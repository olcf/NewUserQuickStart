# Welcome to Hands-on New User training (Tony)
 
This training is designed to introduce you to the Oak Ridge Leadership Computing Facility and its resources. 
Also you should never be more than 20 minutes away from and hands-on exercise. 
For this training you will want to have a browser window open and an ssh terminal open.

 
## Resources Overview (Tony)
 
We'll begin with an overview of Lux, our AMD-based supercomputer built on HPE ProLiant XD685 nodes.
 
Since it is easiest to do this from pictures, lets go to the Lux docs:
https://docs.olcf.ornl.gov/systems/lux_user_guide.html#system-overview

## Getting a project

Lux allocations are distributed by means of [Genesis Mission](https://www.energy.gov/undersecretaryforscience/genesis-mission/genesis-mission) RFA projects.

### Getting access to Lux

## Projects and accounts

### Projects

Projects, not users, are associated with Lux.
Projects have associated machines, allocations, and services.

### Accounts

User accounts are associated with projects.

## Login (Tony)
### Hands-on Finding Jupyter terminal (Tony)
If you do not have an ssh terminal:
1. Open and tab on your browser and direct it to https://docs.olcf.ornl.gov/services_and_applications/jupyter/overview.html#access.
2. Then follow the directions there to access the moderate JupyterHub if you are a Lux user and choose one of the CPU labs.
3. Once you are in, find the "terminal icon". Now you will be ready to do the first hands-on.
 
There are many more uses for OLCF Jupyter Hub and you can find them in the Jupyter at OLCF guide. https://docs.olcf.ornl.gov/services_and_applications/jupyter/overview.html
 
### How to login to Lux (Tony)
 
Once you have a terminal open (either through Jupyter or by opening a terminal program on your computer).
You can login to Lux by executing the following command
 
```
$ ssh <your username>@lux.olcf.ornl.gov
```
 
Replace `<your username>` with your actual username.

 
After you press enter, you will be asked to enter your PASSCODE
 
```
$ ssh <your username>@lux.olcf.ornl.gov
Enter PASSCODE:
```
 
Type in your PIN followed by the six digits shown on your RSA token in one continuous sequence (no spaces). 
You will not see anything being typed on screen, THIS IS NORMAL. 
SSH does give you any visual feedback when typing your PASSCODE, but it is still receiving your key presses. 
Just type the full PASSCODE on your keyboard normally and press enter.
 
If this is your first time ever logging in and you've not set your PIN before, follow the steps in [Activating a New SecurID Fob in the docs](https://docs.olcf.ornl.gov/connecting/index.html#activating-a-new-securid-fob).
 
If your SSH operation succeeds, you should be placed in your home directory on Lux
 
```
[subil@login1.lux ~]$ pwd
/ccs/home/subil
```

### Clone the NewUserQuickStart repository

Parts of this new user training will have hands on portions. 
So clone this repository into your home directory with

```
git clone https://github.com/olcf/NewUserQuickStart
```

And navigate to the Lux directory
```
cd NewUserQuickStart
cd Lux
```
 
### Authentication with RSA tokens (Tony)
 
In an earlier section, we covered logging into Lux using SSH and with your RSA token. 
Let's talk a bit more about what we're doing here.
 
We are using 2-factor authentication via user-selected PINs and RSA securID token. 
The numbers on the RSA securID token change every 30 seconds. 
Entering your PIN+tokencode is the only login method available. 
Using other methods (password, public key, etc) are not allowed.
 
#### RSA terminology
* tokencode - the 6 digit number on your RSA token
* PIN - an alphanumeric string of 4-8 characters known only to you
* PASSCODE - your PIN followed by the current tokencode without any spaces
 
#### Common Login Issues
 
SSH will not prompt you for your username, so make sure that when you SSH you are using the full `ssh <your username>@lux.olcf.ornl.gov`.
 
Your RSA token might get out of sync with the server. So sometimes you might be prompted for 'next tokencode'
```
Enter PASSCODE:
Wait for the tokencode to change, then enter the new tokencode :
```
When this happens, enter only the tokencode your RSA token generates. 
Don't enter the PIN. 
In general, when it asks for PASSCODE, enter the PIN+tokencode. 
For any other case, the terminal will explicitly tell you what it wants you to do.
 
Sometimes you might encounter a message that looks like "Connection closed by <ip address>" after you correctly enter your PASSCODE. 
This usually indicates that your account no longer has access to the particular system you are trying to SSH to. 
Your account's access to systems is tied to your project. 
So when your project's access to a system expires, you lose access to that system.
 
 
If your PASSCODE has failed twice i.e. you are being prompted to enter your PASSCODE for the third time in a row, let the tokencode change before you try entering your PASSCODE again (to avoid getting locked out).
 
If you find that you keep entering the PASSCODE correctly but it fails to log you in, its possible you may have been locked out. 
Send an email to help@olcf.ornl.gov with the information on what you are seeing. 
If your account is locked, the OLCF Help Desk can unlock it for you.

 
## User Guides Overview
OLCF has users guides for its compute systems, data management tools and polices. 
They have examples that cover the basics that you need to know to run on our system. 
Let's start with a hands-on to help you find and navigate those guides.

### OLCF User Guide Hands On
Open a browser tab and go to https://docs.olcf.ornl.gov.
Select the "Systems" option in the left menu bar.

1.	Open Rike guide: Raise your virtual hand when it is open.

2.	Name one visualization tool available on Riker.

3.	What Riker batch queue has the longest available run time?

Close the Riker system guide on the left and open the Lux user guide.
Raise your virtual hand when it is open.

1.	Name one profiling application available on Lux that is described in the guide.

2.	Find the Thread Mapping examples in the running jobs section; What is the `srun` command that ensures that the MPI tasks will be distributed across sockets in a cyclic (round-robin) manner?

3.	Find the Tips and Tricks section; Read the name of one tip listed in that section.

[//]: # (todo - Containers, Torch)

## Filesystems and Storage

### Overview

OLCF has a Network Files system (NFS) that you land on when you login.
This is a small secure filesystem that is provisioned to hold your most important data.
This is the best place for your executables and small important data. It is backed up.

OLCF also has a large parallel filesystem, Orion Lustre, for Lux that you should use to hold your large production data for simulation campaigns or machine learning data and models while you are running.
Orion is not backed up and data older than 90 days are purged.

OLCF storage systems have different areas designated for induvial user storage and project level storage that is controlled by the file permissions. 
Please make sure that data that is to be shared with multiple project members is in the project storage.
This becomes especially important as people leave your project.

For details see our [Data Storage and Transfers Guide]( https://docs.olcf.ornl.gov/data/index.html).

Longer term storge is available in OLCF’s nearline storge system called Kronos.
Kronos is mounted on the moderate security enclave Data Transfer Nodes (`dtn.ccs.ornl.gov`) and is accessible via Globus at the “OLCF Kronos” collection.
Standard UNIX commands and tools can also be used to interact with Kronos (scp, rsync, etc.).

See the Kronos section of our [Data Storage and Transfers guide](https://docs.olcf.ornl.gov/data/index.html#kronos-nearline-archival-storage-system)

### Hands-on Storage Areas

Login to Lux and go to your individual user storage called “scratch”:

Lux (Orion) :

```
cd /lustre/orion/[projid]/scratch/[userid]
ls
```

You can also do:

```
cd $MEMBERWORK/[projid]
ls
```

Now let’s look at the project level storage, proj-shared:

```
cd /lustre/orion/[projid]/proj-shared/
ls

```

You can also do:
```
cd $PROJWORK/[projid]/
ls
```

And for sharing between projects:
```
cd /lustre/orion/[projid]/world-shared/
ls
```

You can also do:
```
cd $WORLDWORK/[projid]
ls
```

### Best practices (Jordan)

## Programming and Compiling (HPC) (Tony)

Documentation on modules and compilers: https://docs.olcf.ornl.gov/systems/lux_user_guide.html#programming-environment

### Lmod

[//]: # (todo: is this section accurate enough?)
Lux supports users from a wide range of scientific disciplines. 
Different users have different software needs. 
Some users might need to use different versions of the same software. 
In order to accommodate this, Lux uses Lmod. 
Lmod manages software installed on Lux in the form of 'modules'. 
You can get access to a specific software or package or library you need by 'loading' the specific module (provided it is available on Lux).

For example, if you want to use the `hipcc` compiler which is part of AMD's ROCm software stack, you may want to consider the version of the default loaded `rocm` module.

```shell
$ hipcc --version
HIP version: 7.2.53211-97f5574fe2
AMD clang version 22.0.0git (https://github.com/RadeonOpenCompute/llvm-project roc-7.2.4 26084 f58b06dce1f9c15707c5f808fd002e18c2accf7e)
Target: x86_64-unknown-linux-gnu
Thread model: posix
InstalledDir: /opt/rocm-7.2.4/lib/llvm/bin
Configuration file: /opt/rocm-7.2.4/lib/llvm/bin/clang++.cfg

$ module load rocm/7.14.0
...
$ hipcc --version
HIP version: 7.14.60850-0000000
AMD clang version 23.0.0git (https://github.com/ROCm/llvm-project.git 46fcb339fb61119b337f973c7ca9e710a319fdd0+PATCHED:440716f8b87be9d8e20ed910e10e5b6d14d57cf6)
Target: x86_64-unknown-linux-gnu
Thread model: posix
InstalledDir: /opt/rocm-7.14.0/lib/llvm/bin
Configuration file: /opt/rocm-7.14.0/lib/llvm/bin/clang++.cfg
```

If you want to use a specific version of the ROCm software stack, you can check which versions are available by running `module spider rocm`.
```shell
$ module spider rocm

------------------------------------------------------------------------------------------------------------------------------------------
  rocm:
------------------------------------------------------------------------------------------------------------------------------------------
     Versions:
        rocm/7.2.4
        rocm/7.14.0

------------------------------------------------------------------------------------------------------------------------------------------
  For detailed information about a specific "rocm" package (including how to load the modules) use the module's full name.
  Note that names that have a trailing (E) are extensions provided by other modules.
  For example:

     $ module spider rocm/7.14.0
------------------------------------------------------------------------------------------------------------------------------------------
```

You can see the full list of modules available to load by simply executing `module spider` without a module name given.

```shell
$ module spider

------------------------------------------------------------------------------------------------------------------------------------------
The following is a list of the modules and extensions currently available:
------------------------------------------------------------------------------------------------------------------------------------------
  DefApps: DefApps

  amd-llvm: amd-llvm/7.2.4, amd-llvm/7.14.0

  amdblis: amdblis/5.3

  amdlibflame: amdlibflame/5.3

  aocl-compression: aocl-compression/5.3

  aocl-crypto: aocl-crypto/5.3

  aocl-libmem: aocl-libmem/5.3

  aocl-sparse: aocl-sparse/5.3

  binutils: binutils/2.46.1

  cmake: cmake/3.31.11

  core: core/1

  gcc: gcc/14.4.0

  git: git/2.53.0

  git-lfs: git-lfs/3.7.1


<truncated for space>
```

And you can load a specific version of a module like rocm 7.14.0 specifying the version number in the `module load` command like so:

```shell
$ module load rocm/7.14.0
```

If a specific version number is not specified, it will load a system defined default version (in the case of `rocm`, the default version loaded is 7.2.4).


`module load` does a few things, chief among which is it updates some environment variables that the OS uses to look for software or libraries.
You can see information about a module and a summary of what changes are made when you execute a `module show` operation.

```shell
$ module show rocm
------------------------------------------------------------------------------------------------------------------------------------------
   /sw/lux/modules/rocm/7.2.4.lua:
------------------------------------------------------------------------------------------------------------------------------------------
help([[ROCm Toolkit v7.2.4]])
whatis("Defines the system paths and environment variables required for the ROCm Toolkit.")
setenv("ROCM_PATH","/opt/rocm-7.2.4")
setenv("HIP_LIB_PATH","/opt/rocm-7.2.4/lib")
prepend_path("PATH","/opt/rocm-7.2.4/bin")
prepend_path("MANPATH","/opt/rocm-7.2.4/share/man")
prepend_path("CMAKE_PREFIX_PATH","/opt/rocm-7.2.4/lib/cmake/hip")
prepend_path("LD_LIBRARY_PATH","/opt/rocm-7.2.4/lib")
prepend_path("LD_LIBRARY_PATH","/opt/rocm-7.2.4/lib/rocprofiler")
prepend_path("LD_LIBRARY_PATH","/opt/rocm-7.2.4/lib/roctracer")
prepend_path("PKG_CONFIG_PATH","/usr/lib64/pkgconfig")
```

At any time you can check the modules that are currently loaded by running `module list`

```shell
$ module list

Currently Loaded Modules:
  1) xalt/3.2.4   3) tmux/3.6a        5) rocm/7.2.4   7) openmpi/5.0.10   9) DefApps
  2) core/1       4) amd-llvm/7.2.4   6) ucx/1.22.0   8) ucc/1.8.0
```

> [!NOTE]
> For a more compact, or machine-readable output, try `module -t list` (`-t` is for terse).

You may notice that there are some modules you have not explicitly loaded in the list, in addition to modules such as `rocm` that you have loaded.
This is because Lux loads a default set of modules every time you log in.
Chief among the default modules is a `rocm` version, namely `rocm/7.2.4`.
Lux as a machine contains most of its computational power in its AMD GPUs (MI355X).
Thus, compiling and programming GPU codes is of such importance that a tested ROCm module is loaded by default.

Unlike Frontier, Lux programming environments are more free-form collections of modules.
Programming environments typically consist of a compiler and some basic dependencies, such as MPI and ROCm.

You can find existing programming environments on Lux utilizing the Lmod command `module avail`.

```shell
$ module avail

---------------------------------------------- [ amd-llvm/7.2.4, rocm/7.2.4, openmpi/5.0.10 ] -----------------------------------------------
   cp2k/2026.1    lammps/20260704    osu-micro-benchmarks/7.5.2

---------------------------------------------------- [ amd-llvm/7.2.4, openmpi/5.0.10 ] -----------------------------------------------------
   amdfftw/5.3    amdscalapack/5.3    hdf5/1.14.6    netcdf-c/4.10.0    netcdf-fortran/4.6.2

------------------------------------------------------ [ amd-llvm/7.2.4, rocm/7.2.4 ] -------------------------------------------------------
   kokkos/5.1.1    mpich/5.0.1    openmpi/5.0.10 (L)

<snip>

---------------------------------------------------------------- [ core/1 ] -----------------------------------------------------------------
   aocl-compression/5.3    binutils/2.46.1    git/2.53.0            patchelf/0.17.2    rust/1.96.0
   aocl-crypto/5.3         cmake/3.31.11      hpcviewer/2026.1.1    pciutils/3.7.0     tmux/3.6a    (L)
   aocl-libmem/5.3         git-lfs/3.7.1      libdrm/2.4.131        python/3.14.5      vim/9.2.0000

------------------------------------------------------------- [ Base Modules ] --------------------------------------------------------------
   DefApps        (L)      amd-llvm/7.14.0        gcc/14.4.0             rocm/7.2.4  (L,D)    xalt/3.2.4 (L)
   amd-llvm/7.2.4 (L,D)    core/1          (L)    miniforge3/26.3.2-3    rocm/7.14.0
```

The delimiter row is your “programming environment” as a list of modules and the modules underneath are optional modules that are managed by the programming environment.
These rows list modules currently loaded, and so `module avail` shows your current "programming environment."

The bottom two delimiter rows, `core/1` and `Base Modules` are basic modules that can be loaded and sometimes replace existing loaded modules.

For example, if you loaded `rocm/7.14.0` in the example below, you would have see the following output.

```shell
$ module load rocm/7.14.0

Inactive Modules:
  1) openmpi

Due to MODULEPATH changes, the following have been reloaded:
  1) ucc/1.8.0     2) ucx/1.22.0

The following have been reloaded with a version change:
  1) rocm/7.2.4 => rocm/7.14.0
```

You can find more information about programming environments on Lux on our [User Guide - Programming Envrionment](https://docs.olcf.ornl.gov/systems/lux_user_guide.html#id3)

Here's a list of the useful commands we've seen so far:
`module load` - load a module so that it becomes available to use
`module show` - show more information about a particular module
`module list` - show list of currently loaded modules
`module spider` - show list of modules and their versions, or if a module name is specified, show the versions of those modules that are available to load
`module avail` - view available modules for our current programming environment

### Compiling

#### Hello, world
#### Hello, MPI
#### Hello, RCCL
#### Hello, jobstep

### Building containers (Subil?)

#### Podman
#### Apptainer

## Running Jobs

### Slurm

### Example: PyTorch

### Example: Container (Subil?)

## Lux Kubernetes (Subil)

### Rancher

https://console.apps.slate-mod.ccs.ornl.gov/dashboard/home

* Kubeconfig

### CLI

* `kubectl`
* `rancher-cli` (ignore if not in docs)

## Image Registry (Subil)

Harbor https://harbor.ccs.ornl.gov/harbor/projects

## Globus
 
* Globus is a fast and reliable way to move files between OLCF systems and between OLCF and other institutions.
* It has a convenient Web-interface at globus.org that you log into with a username and password.
* Transfers are done by activating “Collections” which are portals into the OLCF's file systems and to those of participating institutions.
* Globus is the recommended way to move files between OLCF systems and between OLCF and exterior systems.
 
For this exercise we will setup your globus.org username and password. You can skip this if you have a globus ID.

Note: Globus is not controlled by OLCF and its help and login pages and option change without warning. This hands-on is based on Globus pages from 05-02-24. Even if the specific Globus pages change, this tutorial should be close to what is needed to get a globus username and password.
 
### Hands-on GlobusID
 
1. Open a browser and direct it to globusid.org.
2. Select "create GlobusID" and follow the instructions
3. Remember your globusID and password someplace safe.
 
Now try to log in: 

1. Go to globus.org and click "Login"
  
2.  Find the "use Globus ID" link and use your GlobusID to login.  The Oak Ridge National Laboratory login is only for ORNL staff.
3. You should see the Globus "File Manager" when you are logged in.
 
### Activating a Globus Collection
 
Activating the OLCF Globus Collection is done using your OLCF username and Token Passcode. Think of it as logging in to an OLCF filesystem.

Collections stay activated for three days, so you don’t need to enter your credentials for each transfer, and you can run a transfer workflow during a simulation.
  
The OLCF Moderate Collection is called “OLCF DTN (Globus 5)”. 
 
The following exercise assumes that you have logged in using steps like those in the Hands-On Globus-ID exercise above. 
 
1.	Type "OLCF" in the Collections bar. A list of options for OLCF will form below, select the “OLCF DTN (Globus 5)” Collection.

2.	If Globus pings you to associate your Globus ID with OLCF credentials, follow the instructions that it gives.

3.	 When prompted, sign in with your OLCF username and PIN+ PASSCODE. (If you are doing this from Odo, use you XCAMS/UCAMS username and password to login.)
 
You will need to enter a path in the PATH bar to access files. To see you home area on Lux enter:

/ccs/home/<your_user_id>

In this exercise we will access the parallel filesystem using Globus: 
 
* Lux users: 

You can reach Orion Lustre from the “OLCF DTN (Globus 5)” Collection. You do so by entering the path to them in the Path bar.
 
Path to Orion `/gpfs/orion/<<your_project_ID>>`
 
4.	Find the Path bar in the file manager and enter the path listed above that is appropriate for the resource that you are working on. 
 
You should see three directories listed in the file manager:

* scratch - personal workspace on the parallel file system; purged every 90 days.
* proj-shared – project level workspace on the parallel file system; purged every 90 days.
* world-shared - workspace on the parallel file system where files can be shared between projects; purged every 90 days.
 
5.	From the File Manager, you can click on those work spaces to see the files within each. 


If you want to setup a personal Globus Collection on your laptop, follow these instructions: [https://www.globus.org/globus-connect-personal](https://www.globus.org/globus-connect-personal).

 
## Globus Data Transfer

The Department of Energy, [Energy Sciences Network]( https://www.es.net/about/),  ESnet has deployed read-only GridFTP servers and Globus Collections for data transfer testing purposes. We are going to use one of those, called "ESnet Denver DTN (Anonymous read only testing)" and its test files to do the next two exercises.

Let's move a test file from an ESnet test collection into our scratch workspace.

1. Go to the browser tab that has the Globus File Manager in it and find the panels options in the upper right. 

2. Click on the picture of the double panel. After that, you should have panels on the left and right that each have a Collection and a Path bar.

3. Enter "ESnet Denver DTN (Anonymous read only testing)" in the left Collection bar.

4. You will see a set of folders with different sized files and folders listed in the File Manager. We are going to transfer the 10MB file called `10M.dat`.  

5. In the right Collection bar enter the  “OLCF DTN (Globus 5)”, then enter the path to your scratch directory `/gpfs/orion/<<your_project_ID>>/scratch/<<user_ID>>’ in the Path bar. 

6. To move the file "10M.dat" from the "ESnet Denver DTN (Anonymous read only testing)" to your OLCF parallel file system scratch area, simply drag and drop "10M.dat" from panel to panel. You can also select "10M.dat" and click on the arrows to move it.
 
Globus will notify you when the transfer is complete. 

You can access Globus collections, that you have credentials for, at institution that has them. For example, if you are a NERSC user, you can access their file systems via their globus Collection too, you just need to activate the collection with your NERSC credentials. 

### A Few Tips for Using Globus

1. When transferring files between parallel filesystems, it is best to move multiple files at once, such as by transferring an entire folder. Globus will optimize the transfer by using parallel streams.

2. When transferring files to an HPSS at another User Facility, first create a tar archive. HPSS is optimized for handling large files and may experience performance issues if many small files are transferred individually. A large number of small files can overwhelm the HPSS cache, impacting performance for all users.
 
[OLCF Data Storage and Transfers Guide]( https://docs.olcf.ornl.gov/data/index.html#data-storage-and-transfers)


## Training Opportunities
 
- Keep an eye out for upcoming trainings on our [Training Calendar](https://www.olcf.ornl.gov/for-users/training/training-calendar)
- Missed a training? All our trainings are recorded and are listed in the [Training Archive](https://docs.olcf.ornl.gov/training/training_archive.html)
- tell us what kinds of training you would like to see
 
## Getting Help
 
If you're stuck, the OLCF Help Desk is here to help! You can email us at help@olcf.ornl.gov 
