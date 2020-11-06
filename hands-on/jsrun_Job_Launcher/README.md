# `jsrun` Job Launcher

When running programs on a workstation, most of the time you can simply execute `./a.out` and wait for the results. On most HPC clusters, you must use a "batch scheduler" to request one or more compute nodes to run on and a "job launcher" to execute your program on the compute node(s) you were allocated. In this challenge, you will learn the basics of how to launch jobs on Summit with IBM's `jsrun` job launcher.

## Summit Nodes

Before getting started, it's instructive to look at a diagram of a Summit node to understand the terminology we'll use. 

Each Summit node contains 2 IBM Power9 CPUs and 6 NVIDIA V100 GPUs (1 CPU and 3 GPUs per socket). Each of the Power9 CPUs have 21 physical cores - each with 4 hardware threads. So, looking at the image below, physical core 0 contains hardware threads 000-003, physical core 1 contains hardware threads 004-007, etc. The numbering of hardware threads will be important as we proceed.

<br>
<center>
<img src="images/jsrunVisualizer-nodeLegend.png" style="width:100%">
</center>
<br>

## Resource Sets

Resource sets are a central theme when discussing `jsrun`, so we should begin by defining them. 

* A <u>resource set</u> is a collection of resources (e.g., CPU cores, GPUs) that can be assigned to one or more tasks. 
* All resource sets are the same for a single `jsrun` command
* A resource set cannot span more than 1 node.

So a resource set might simply be a whole node (i.e., 42 physical CPU cores and 6 GPUs) or a subset of a node (e.g., 1 physical CPU core and 1 GPU). We'll use color-coded images like the one below to describe resource sets throughout this document, where each different colored set of CPUs and GPUs is a different resource set. In the diagram, in the M[T] numbering scheme, M represents the MPI rank ID and T represents the OpenMP thread ID. So for example, 2[1] represents MPI rank 2, OpenMP thread 1. This will become clearer as we continue below.

<br>
<center>
<img src="images/jsrunVisualizer-layout2.png" style="width:80%">
</center>
<br>

## `jsrun` Format

A `jsrun` command must contain the number of resource sets, a definition of the resource sets, and the program to be launched (along with its arguments). The basic format is as follows:

```c
jsrun [ # of resource sets ] [ definition of resource sets ] program [ program args ]
```

### Constructing a `jsrun` Command

The first step to contructing a `jsrun` command is to define the resource sets you want to use. The next step is to decide how many resource sets you want to use. This can be accomplished with the following set of flags:

<br>

| flag (long)      | flag (short) | description                               |
|----------------- | ------------ | ------------------------------------------|
| `--nrs`          | `-n`         | Number of resource sets                   |
| `--cpu_per_rs`   | `-c`         | Number of physical cores per resource set |
| `--gpu_per_rs`   | `-g`         | Number of GPUs per resource set           |
| `--tasks_per_rs` | `-a`         | Number of tasks per resource set          |

<br>
There is another flag we'll cover as well, but for now, let's just move forward with these.

## Hello_jsrun

To demonstrate the use of `jsrun`, we will use a simple "Hello, World!" type program that prints out information about the resources being used in a job. To follow along, you can clone the `Hello_jsrun` repository within this challenge's directory:

```c
$ git clone https://code.ornl.gov/t4p/Hello_jsrun.git
```

After cloning, move into the directory, load the cuda module, and compile with `make`:

```c
$ cd Hello_jsrun
$ module load cuda
$ make
```

Then copy the `submit.lsf` file into the `Hello_jsrun/` directory:

```c
$ cp ../submit.lsf .
```

## Job Step Viewer

The [Job Step Viewer](https://jobstepviewer.olcf.ornl.gov/) provides a graphical view of an application's runtime layout on Summit. It allows users to preview and quickly iterate with multiple jsrun options to understand and optimize job launch. It is a convenient tool that allows you to visualize and verify you are configuring your `jsrun` options in the way you expect.

We recommend attempting Job Step Viewer Challenge in conjunction with this challenge. You should go through the first example or two following this section to get an understanding of how the `jsrun` command works, then re-run the examples, integrating the Job Step Viewer into your submission script. Then you can continue to use the Viewer as you go through the remaining examples and visualize your submissions as you go.

## Example 1

As a first example, let's try to create the layout shown in the image below. Here, we are essentially splitting up the resources on our node among 6 resource sets, where each resource set is shown as a different color and contains 7 physical CPU cores and 1 GPU. Recall that in the M[T] numbering scheme, M represents the MPI rank ID and T represents the OpenMP thread ID. So, for example, 2[0] represents MPI rank 2 - OpenMP thread 0. Based on the image, this means that each resource set contains 1 MPI rank and 1 OpenMP thread. 

<br>
<center>
<img src="images/jsrunVisualizer-layout1.png" style="width:80%">
</center>
<br>

Now let's try to create the `jsrun` command that will give us this layout. The first thing we need to do is define our resource sets. As shown in the image, each resource set will contain 7 physical CPU cores (`-c7`), 1 GPU (`-g1`), 1 MPI rank (`-a1`), and 1 OpenMP thread. To set the number of OpenMP threads, we will use the `OMP_NUM_THREADS` environment variable. Now that we have defined our resource sets, we can use `-n6` to create 6 of them.

So you should edit the `submit.lsf` file to read

```c
export OMP_NUM_THREADS=1

jsrun -n6 -c7 -g1 -a1 ./hello_jsrun | sort
```

After running this code with `bsub submit.lsf`, you should find the following information in the output file `testing_jsrun.JOBID`:


```
---------- MPI Ranks: 6, OpenMP Threads: 1, GPUs per Resource Set: 1 ----------
MPI Rank 000, OMP_thread 00 on HWThread 001 of Node h49n16 - RT_GPU_id 0 : GPU_id 0 
MPI Rank 001, OMP_thread 00 on HWThread 029 of Node h49n16 - RT_GPU_id 0 : GPU_id 1 
MPI Rank 002, OMP_thread 00 on HWThread 058 of Node h49n16 - RT_GPU_id 0 : GPU_id 2 
MPI Rank 003, OMP_thread 00 on HWThread 089 of Node h49n16 - RT_GPU_id 0 : GPU_id 3 
MPI Rank 004, OMP_thread 00 on HWThread 117 of Node h49n16 - RT_GPU_id 0 : GPU_id 4 
MPI Rank 005, OMP_thread 00 on HWThread 145 of Node h49n16 - RT_GPU_id 0 : GPU_id 5
```

As you can see from the output, the program prints the MPI rank ID and the OpenMP thread ID as well as the hardware thread each rank/thread ran on, the GPU(s) each rank/thread had available to it, and the hostname of the compute node. So, for example, MPI rank 0 (and its OpenMP thread 0) ran on hardware thread 001 with GPU 0 available to it, and the hostname of the compute node was h49n16. This corresponds to the "red" resource set shown in the image above. Looking at the rest of the output shows that we have successfully produced the results shown in the image.

**ADDITIONAL DETAILS:** 

* The actual hardware thread (within a physical core) that an MPI rank runs on will vary from run to run.
* In the output, `GPU_id` represents the node-level GPU ID (numbered 0-5) as shown in the image. 
* In the output, `RT_GPU_id` represents the GPU ID as seen from the CUDA runtime. Basically, within each resource set, the runtime numbers its GPUs starting from 0, which is why `RT_GPU_id` is 0 for all rows above.

## Example 2

For the next example, let's run the same program but use 2 OpenMP threads to create the layout shown in the image below. Although this example is very similar to the first one, it will help point out a subtlety that might otherwise be overlooked.

<br>
<center>
<img src="images/jsrunVisualizer-layout2.png" style="width:80%">
</center>
<br>

To create this layout, we will first try to simply change the number of OpenMP threads to 2 and rerun the same command we used in Example 1. To do so, edit the `submit.lsf` file to read

```c
$ export OMP_NUM_THREADS=2
$ jsrun -n6 -c7 -g1 -a1 ./hello_jsrun | sort
```

Then submit the job to run on a compute node with the following command:

```c
$ bsub submit.lsf
```

After the job completes, you should see output similar to that below in the `testing_jsrun.JOBID` file.

```
---------- MPI Ranks: 6, OpenMP Threads: 2, GPUs per Resource Set: 1 ----------
MPI Rank 000, OMP_thread 00 on HWThread 001 of Node h49n16 - RT_GPU_id 0 : GPU_id 0 
MPI Rank 000, OMP_thread 01 on HWThread 002 of Node h49n16 - RT_GPU_id 0 : GPU_id 0 
MPI Rank 001, OMP_thread 00 on HWThread 029 of Node h49n16 - RT_GPU_id 0 : GPU_id 1 
MPI Rank 001, OMP_thread 01 on HWThread 030 of Node h49n16 - RT_GPU_id 0 : GPU_id 1 
MPI Rank 002, OMP_thread 00 on HWThread 057 of Node h49n16 - RT_GPU_id 0 : GPU_id 2 
MPI Rank 002, OMP_thread 01 on HWThread 056 of Node h49n16 - RT_GPU_id 0 : GPU_id 2 
MPI Rank 003, OMP_thread 00 on HWThread 088 of Node h49n16 - RT_GPU_id 0 : GPU_id 3 
MPI Rank 003, OMP_thread 01 on HWThread 091 of Node h49n16 - RT_GPU_id 0 : GPU_id 3 
MPI Rank 004, OMP_thread 00 on HWThread 117 of Node h49n16 - RT_GPU_id 0 : GPU_id 4 
MPI Rank 004, OMP_thread 01 on HWThread 119 of Node h49n16 - RT_GPU_id 0 : GPU_id 4 
MPI Rank 005, OMP_thread 00 on HWThread 145 of Node h49n16 - RT_GPU_id 0 : GPU_id 5 
MPI Rank 005, OMP_thread 01 on HWThread 146 of Node h49n16 - RT_GPU_id 0 : GPU_id 5 
```

From the output, we can see that each MPI rank now has 2 OpenMP threads as intended. However, both OpenMP threads are running on the same physical core instead of on separate physical cores as shown in our image above. For example, OpenMP threads 0 and 1 of MPI rank 0, ran on hardware threads 001 and 002, which are both on the same physical core. So why did this happen? Each resource set has 7 physical cores available to it, so how do we use them? This brings us to a new flag:

<br>

| flag (long) | flag (short) | description                                                          |
|------------ | ------------ | ---------------------------------------------------------------------|
| `--bind`    | `-b`         | Binding of tasks within a resource set. Can be none, rs, or packed:#.|  

<br>

`--bind` allows you to set the number of physical cores available to an MPI task (to do things like spawn OpenMP threads on). By default, it is set to `-bpacked:1`, which means each MPI rank only has 1 physical core available to it. So when we spawned our 2 OpenMP threads from each MPI rank, they only had 1 physical core to run on (although 4 hardware threads). In some cases, this is undesired behavior that can slow down application performance.

<br>

If we want to run each OpenMP thread on its own physical core, we would need to set the `#` in `-bpacked:#` to the number of OpenMP threads we desire. So for our example, we would want `-bpacked:2`. Let's try that. Edit the `submit.lsf` file to read

```c
$ export OMP_NUM_THREADS=2
$ jsrun -n6 -c7 -g1 -a1 -bpacked:2 ./hello_jsrun | sort
```

After running the job (`bsub submit.lsf`), you should see the following output:

```c
---------- MPI Ranks: 6, OpenMP Threads: 2, GPUs per Resource Set: 1 ----------
MPI Rank 000, OMP_thread 00 on HWThread 001 of Node h49n16 - RT_GPU_id 0 : GPU_id 0 
MPI Rank 000, OMP_thread 01 on HWThread 004 of Node h49n16 - RT_GPU_id 0 : GPU_id 0 
MPI Rank 001, OMP_thread 00 on HWThread 029 of Node h49n16 - RT_GPU_id 0 : GPU_id 1 
MPI Rank 001, OMP_thread 01 on HWThread 032 of Node h49n16 - RT_GPU_id 0 : GPU_id 1 
MPI Rank 002, OMP_thread 00 on HWThread 057 of Node h49n16 - RT_GPU_id 0 : GPU_id 2 
MPI Rank 002, OMP_thread 01 on HWThread 060 of Node h49n16 - RT_GPU_id 0 : GPU_id 2 
MPI Rank 003, OMP_thread 00 on HWThread 088 of Node h49n16 - RT_GPU_id 0 : GPU_id 3 
MPI Rank 003, OMP_thread 01 on HWThread 092 of Node h49n16 - RT_GPU_id 0 : GPU_id 3 
MPI Rank 004, OMP_thread 00 on HWThread 117 of Node h49n16 - RT_GPU_id 0 : GPU_id 4 
MPI Rank 004, OMP_thread 01 on HWThread 120 of Node h49n16 - RT_GPU_id 0 : GPU_id 4 
MPI Rank 005, OMP_thread 00 on HWThread 145 of Node h49n16 - RT_GPU_id 0 : GPU_id 5 
MPI Rank 005, OMP_thread 01 on HWThread 148 of Node h49n16 - RT_GPU_id 0 : GPU_id 5
```

Success! Now, from the hardware thread IDs, we can see that each OpenMP thread ran on a different physical core as we intended.

## Example 3

For our next example, we will split the resources on our node among 2 resource sets, with 1 resource set per socket. The desired layout will look like the image below. Here, we can see that each resource set contains 21 physical cores (`-c21`), 3 GPUs (`-g3`), and 3 MPI ranks (`-a3`; each with 1 OpenMP thread).

<br>

<center>
<img src="images/jsrunVisualizer-layout3.png" style="width:80%">
</center>

<br>

Based on what we've learned so far, we might try the following commands to create this layout:

```c
$ export OMP_NUM_THREADS=1
$ jsrun -n2 -c21 -g3 -a3 -bpacked:1 ./hello_jsrun | sort

```

This results in the following output:

```c
---------- MPI Ranks: 6, OpenMP Threads: 1, GPUs per Resource Set: 3 ----------
MPI Rank 000, OMP_thread 00 on HWThread 000 of Node h50n12 - RT_GPU_id 0 1 2 : GPU_id 0 1 2 
MPI Rank 001, OMP_thread 00 on HWThread 004 of Node h50n12 - RT_GPU_id 0 1 2 : GPU_id 0 1 2 
MPI Rank 002, OMP_thread 00 on HWThread 009 of Node h50n12 - RT_GPU_id 0 1 2 : GPU_id 0 1 2 
MPI Rank 003, OMP_thread 00 on HWThread 089 of Node h50n12 - RT_GPU_id 0 1 2 : GPU_id 3 4 5 
MPI Rank 004, OMP_thread 00 on HWThread 092 of Node h50n12 - RT_GPU_id 0 1 2 : GPU_id 3 4 5 
MPI Rank 005, OMP_thread 00 on HWThread 096 of Node h50n12 - RT_GPU_id 0 1 2 : GPU_id 3 4 5
```

From the output, we can see that we have created our 2 resource sets (each with 21 physical cores and 3 GPUs), and that MPI ranks 0, 1, 2 are on hardware threads 002, 004, and 009, repsectively and have access to GPUs 0, 1, 2 (i.e., are on the first socket), and that MPI ranks 3, 4, 5 are on hardware threads 089, 092, 096, respectively and have access to GPUs 3, 4, 5 (i.e., are on the second socket). Success!

## Summary of Options Covered Here

While this is not intended to be a comprehensive tutorial on `jsrun`, hopefully it has given you a decent foundation to create your own layouts with the job launcher. The `jsrun` flags we covered in this guide are summarized in the following table:

<br>

| flag (long)             | flag (short) | description                                    |
|------------------------ | ------------ | -----------------------------------------------|
| `--cpu_per_rs`          | `-c`         | Number of physical cores per resource set      | 
| `--gpu_per_rs`          | `-g`         | Number of GPUs per resource set                | 
| `--tasks_per_rs`        | `-a`         | Number of tasks per resource set               |
| `--nrs`                 | `-n`         | Number of resource sets                        | 
| `--bind`                | `-b`         | Binding of tasks within a resource set. Can be none, rs, or packed:#.|  

<br>

These flags will give most users the ability to create the resource layouts they desire but, as mentioned above, this is only a sub-set of the functionality available with `jsrun`. 

## Examples to Try on Your Own

Now that you have the basics down, you can try to create the `jsrun` commands to produce output that matches the images below.

### Example 4

6 resource sets, each with 7 physical CPU cores and 1 GPU - 1 MPI rank per resource set that has 7 OpenMP threads (each thread running on its own physical CPU core)

<br>
<center>
<img src="images/jsrunVisualizer-layout4.png" style="width:80%">
</center>
<br>


### Example 5

2 resource sets, each with 21 physical CPU cores and 3 GPUs - 1 MPI rank per resource set that has 21 OpenMP threads (each thread running on its own physical CPU core)

<br>
<center>
<img src="images/jsrunVisualizer-layout5.png" style="width:80%">
</center>
<br>

### Example 6

6 resource sets, each with 7 physical CPU cores and 1 GPU - 2 MPI ranks per resource set that each have 3 OpenMP threads (each thread running on its own physical CPU core)

<br>
<center>
<img src="images/jsrunVisualizer-layout6.png" style="width:80%">
</center>
<br>

### Example 7

1 resource set that contains 42 physical CPU cores and 6 GPUs - 6 MPI ranks that each have 7 OpenMP threads (each thread running on its own physical CPU core)

<br>
<center>
<img src="images/jsrunVisualizer-layout7.png" style="width:80%">
</center>
<br>

