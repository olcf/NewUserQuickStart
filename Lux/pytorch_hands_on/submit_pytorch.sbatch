#!/bin/bash
#SBATCH -A PROJECT_ID
#SBATCH -J ddp_test
#SBATCH -o logs/ddp_test-%j.o
#SBATCH -e logs/ddp_test-%j.e
#SBATCH -t 00:05:00
#SBATCH -p batch
#SBATCH -N 2
#SBATCH --exclusive

# Load modules
module load rocm/7.2.4
module load miniforge3/26.3.2-3

# Activate your environment
### TODO: change to world-shared dir ###
conda activate $(pwd)/lux_torch_env

# Get address of head node
export MASTER_ADDR=$(hostname -i)

# Needed to bypass MIOpen, Disk I/O Errors
export MIOPEN_USER_DB_PATH="/tmp/my-miopen-cache"
export MIOPEN_CUSTOM_CACHE_DIR=${MIOPEN_USER_DB_PATH}
rm -rf ${MIOPEN_USER_DB_PATH}
mkdir -p ${MIOPEN_USER_DB_PATH}

# Run script

# Notice you can use SLURM environment variables in job submission scripts
# There are many SLURM environment variables, but some helpful ones can be found here: https://www.nccs.nasa.gov/sbatch-environment-variables/

srun -N $SLURM_NNODES -n 16 --gpus 16 --gpus-per-node 8 --cpus-per-task=16  python3 -W ignore -u ./lux_microbench.py --batch-size 1024 --master_addr=$MASTER_ADDR --master_port=3442
