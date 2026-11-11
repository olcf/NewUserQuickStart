#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <hip/hip_runtime.h>
#include <nccl.h>

// Helper macro for checking HIP and RCCL errors
#define RCCLCHECK(cmd) do { \
  ncclResult_t res = cmd; \
  if (res != ncclSuccess) { \
    std::cerr << "RCCL failure " << ncclGetErrorString(res) << " on line " << __LINE__ << std::endl; \
    exit(EXIT_FAILURE); \
  } \
} while(0)

#define HIPCHECK(call) do { \
  hipError_t err = call; \
  if (err != hipSuccess) { \
    std::cerr << "HIP error '" << hipGetErrorString(err) << "' on line " << __LINE__ << std::endl; \
    exit(EXIT_FAILURE); \
  } \
} while(0)

// Simple TCP broadcast/exchange function for ncclUniqueId between Rank 0 and other ranks
void exchange_nccl_id(int rank, int world_size, const char* master_ip, int port, ncclUniqueId* id) {
    if (rank == 0) {
        // Rank 0 generates the unique ID
        RCCLCHECK(ncclGetUniqueId(id));

        // Setup server socket to listen for other ranks
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        int opt = 1;
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        bind(server_fd, (struct sockaddr*)&address, sizeof(address));
        listen(server_fd, world_size - 1);

        std::cout << "[Rank 0] Waiting for connections to share ncclUniqueId...\n";
        for (int i = 1; i < world_size; ++i) {
            int client_sock = accept(server_fd, nullptr, nullptr);
            send(client_sock, id, sizeof(ncclUniqueId), 0);
            close(client_sock);
        }
        close(server_fd);
    } else {
        // Worker ranks connect to Rank 0 to fetch the unique ID
        int sock = 0;
        sockaddr_in serv_addr{};
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        inet_pton(AF_INET, master_ip, &serv_addr.sin_addr);

        // Retry connection loop until Rank 0 is ready
        while (connect(sock = socket(AF_INET, SOCK_STREAM, 0), (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            close(sock);
            usleep(500000); // Sleep 0.5s
        }

        recv(sock, id, sizeof(ncclUniqueId), 0);
        close(sock);
        std::cout << "[Rank " << rank << "] Successfully received ncclUniqueId from Rank 0.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <rank> <world_size> [master_ip]\n";
        return EXIT_FAILURE;
    }

    int rank = std::atoi(argv[1]);
    int world_size = std::atoi(argv[2]);
    const char* master_ip = (argc > 3) ? argv[3] : "127.0.0.1";
    int tcp_port = 12345;

    // 1. Select the AMD GPU corresponding to this process rank
    int num_gpus = 0;
    HIPCHECK(hipGetDeviceCount(&num_gpus));
    if (num_gpus < world_size && num_gpus > 0) {
        std::cout << "[Rank " << rank << "] Warning: world_size (" << world_size
                  << ") > available GPUs (" << num_gpus << "). Wrapping around devices.\n";
    }
    int device_id = rank % (num_gpus > 0 ? num_gpus : 1);
    HIPCHECK(hipSetDevice(device_id));
    // std::cout << "[Rank " << rank << "] Using AMD GPU Device: " << device_id << "\n";

    // sanity check bus ID
    char bus_id[64];
    hipDeviceGetPCIBusId(bus_id, sizeof(bus_id), device_id);
    std::cout << "[Rank " << rank << "] Using AMD GPU Device: " << device_id << " (" << bus_id << ")\n";

    // 2. Bootstrap/Exchange the NCCL Unique ID over TCP
    ncclUniqueId commId;
    exchange_nccl_id(rank, world_size, master_ip, tcp_port, &commId);

    // 3. Initialize RCCL Communicator
    ncclComm_t comm;
    RCCLCHECK(ncclCommInitRank(&comm, world_size, commId, rank));

    // 4. Allocate simple host and device data
    int data_size = 4;
    std::vector<float> h_send(data_size);
    std::vector<float> h_recv(data_size);

    // Populate send buffer with rank-specific values (e.g., Rank 0: [1, 1, 1, 1], Rank 1: [2, 2, 2, 2])
    for (int i = 0; i < data_size; ++i) {
        h_send[i] = static_cast<float>(rank + 1);
    }

    float *d_send, *d_recv;
    HIPCHECK(hipMalloc(&d_send, data_size * sizeof(float)));
    HIPCHECK(hipMalloc(&d_recv, data_size * sizeof(float)));

    HIPCHECK(hipMemcpy(d_send, h_send.data(), data_size * sizeof(float), hipMemcpyHostToDevice));

    // 5. Create a HIP Stream and execute All-Reduce (Sum)
    hipStream_t stream;
    HIPCHECK(hipStreamCreate(&stream));

    std::cout << "[Rank " << rank << "] Executing ncclAllReduce (Sum)...\n";

    RCCLCHECK(ncclAllReduce(d_send, d_recv, data_size, ncclFloat, ncclSum, comm, stream));

    // Synchronize stream
    HIPCHECK(hipStreamSynchronize(stream));

    // 6. Copy results back to host and inspect
    HIPCHECK(hipMemcpy(h_recv.data(), d_recv, data_size * sizeof(float), hipMemcpyDeviceToHost));

    std::cout << "[Rank " << rank << "] Result: ";
    for (int i = 0; i < data_size; ++i) {
        std::cout << h_recv[i] << " ";
    }
    std::cout << "\n";

    // 7. Clean up resources
    HIPCHECK(hipFree(d_send));
    HIPCHECK(hipFree(d_recv));
    HIPCHECK(hipStreamDestroy(stream));
    ncclCommDestroy(comm);

    std::cout << "[Rank " << rank << "] Done!\n";
    return 0;
}
