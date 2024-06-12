# Basic Workflow to Run a Job on Summit

The basic workflow for running programs on HPC systems is 1) set up your programming environment - i.e., the software you need, 2) compile the code - i.e., turn the human-readable programming language into machine code, 3) request access to one or more compute nodes, and 4) launch your executable on the compute node(s) you were allocated. In this exercise, you will perform these basic steps to see how it works.

For this exercise you will compile and run a vector addition program written in C. It takes two vectors (A and B), adds them element-wise, and writes the results to vector C:

```c
// Add vectors (C = A + B)
for(int i=0; i<N; i++)
{
    C[i] = A[i] + B[i];
}
```

## Step 1: Setting Up Your Programming Environment
Many software packages and scientific libraries are pre-installed on Summit for users to take advantage of. Several packages are loaded by default when a user logs in to the system and additional packages can be loaded using environment modules. To see which packages are currently loaded in your environment, run the following command:

```
$ module list
``` 

> NOTE: The `$` in the command above represents the "command prompt" for the bash shell and is not part of the command that needs to be executed.

For this example program, we will use the PGI compiler. To use the PGI compiler, load the PGI module by issuing the following command:

```
$ module load pgi
```

## Step 2: Compile the Code

Now that you've set up your programming environment for the code used in this challenge, you can go ahead and compile the code. First, make sure you're in the `Basic_Workflow/` directory:

```
$ cd ~/OLCF-New-User-quick-start/hands-on/Basic_Workflow
```

> NOTE: The path above assumes you cloned the repo in your `/ccs/home/username` directory.

Then compile the code. To do so, you'll use the provided `Makefile`, which is a file containing the set of commands to automate the compilation process. To use the `Makefile`, issue the following command:

```
$ make
```

Based on the commands contained in the `Makefile`, an executable named `run` will be created.


## Steps 3-4: Request Access to Compute Nodes and Run the Program

In order to run the executable on Summit's compute nodes, you need to request access to a compute node and then launch the job on the node. The request and launch can be performed using the single batch script, `submit.lsf`. If you open this script, you will see several lines starting with `#BSUB`, which are the commands that request a compute node and define your job (i.e., give me 1 compute node for 10 minutes, charge project `PROJID` for the time, and name the job and output file `add_vec_cpu`). You will also see a `jsrun` command within the script, which launches the executable (`run`) on the compute node you were given. 

 In the example script you will replace "Your_Project_ID" with your project ID which will be of the form ABC001. 
To see a full description of the BSUB options and jsrun options see [The Summit Users Guide](https://docs.olcf.ornl.gov/systems/summit_user_guide.html#batch-scripts)
```
#!/bin/bash

#BSUB -P Your_Project_ID
#BSUB -J add_vec_cpu
#BSUB -o add_vec_cpu.%J
#BSUB -nnodes 1
#BSUB -W 10

date

jsrun -n1 -c1 -a1 ./run

```

The flags given to `jsrun` define the resources (i.e., cpu cores, gpus) available to your program and the processes/threads you want to run on those resources (for more information on using the `jsrun` job launcher, please see challenge [jsrun\_Job\_Launcher](../jsrun_Job_Launcher)).

To submit and run the job, issue the following command:

```
$ bsub submit.lsf
```

## Monitoring Your Job

Now that the job has been submitted, you can monitor its progress. Is it running yet? Has it finished? To find out, you can issue the command 

```
$ jobstat -u USERNAME
```

where `USERNAME` is your username. This will show you the state of your job to determine if it's running, eligible (waiting to run), or blocked. When you no longer see your job listed with this command, you can assume it has finished (or crashed). Once it has finished, you can see the output from the job in the file named `add_vec_cpu.JOBID`, where `JOBID` is the unique ID given to you job when you submitted it. You can confirm that it gave the correct results by looking for `__SUCCESS__` in the output file. 

