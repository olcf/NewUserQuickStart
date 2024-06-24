
# Welcome to Hands-on New User training
 
This training is designed to introduce you to the Oak Ridge Leadership Computing Facility and its resources. Also you should never be more than 20 minutes away from and hands-on exercise. For this training you will want to have a browser window open and an ssh terminal open.
 
## Hands-on Finding Jupyter terminal.
If you do not have an ssh terminal:
1. Open and tab on your browser and direct it to https://docs.olcf.ornl.gov/services_and_applications/jupyter/overview.html#access.
 
2. Then follow the directions there to access the moderate Jupyter hub if you are a Frontier of summit user. IF you are using Odo or Ascent follow the directions for the Open Jupyer hub. In either case, choose one of the cpu labs.
 
3. Once you are in, find the "terminal icon". Now you will be ready to do the first hands-on.
 
There are many more uses for OLCF Jupyter Hub and you can find them in the Jupyter at OLCF guide. https://docs.olcf.ornl.gov/services_and_applications/jupyter/overview.html
 
## Resources Overview
 
We'll begin with an overview of Frontier, our exascale super computer.
We will not be covering an overview of Summit today, but you can find one here if you are Summit user. https://github.com/olcf/NewUserQuickStart/blob/master/README.md
 
Since it is easiest to do this from pictures, lets go to the Frontier docs:
https://docs.olcf.ornl.gov/systems/frontier_user_guide.html#system-overview
 
TODO: Insert picture of frontier cabinet and node from USRSE container talk
 
You can also watch [this video giving a more detailed overview of the Frontier hardware](https://vimeo.com/840551316).
 
## How to login to Frontier:
 
Once you have a terminal open (either through Jupyter or by opening a terminal program on your computer), You can login to frontier by executing the following command
 
```
$ ssh <your username>@frontier.olcf.ornl.gov
```
 
Replace `<your username>` with your actual username.
 
If you are using Odo, execute the following instead
 
```
$ ssh <your username>@login1.odo.olcf.ornl.gov
```
 
After you press enter, you will be asked to enter your PASSCODE
 
```
$ ssh <your username>@frontier.olcf.ornl.gov
Enter PASSCODE:
```
 
Type in your PIN followed by the six digits shown on your RSA token in one continuous sequence (no spaces). You will not see anything being typed on screen, THIS IS NORMAL. SSH does give you any visual feedback when typing your PASSCODE, but it is still receiving your key presses. Just type the full PASSCODE on your keyboard normally and press enter.
 
If this is your first time ever logging in and you've not set your PIN before, follow the steps in [Activating a New SecurID Fob in the docs](https://docs.olcf.ornl.gov/connecting/index.html#activating-a-new-securid-fob).
 
If your SSH operation succeeds, you should be placed in your home directory on Frontier or Odo
 
```
[subil@login05 ~]$ pwd
/ccs/home/subil
```
 
 
 
## User Guides Overview
OLCF has users guides for its compute systems, data management tools and polices. They have examples that cover the basics that you need to know to run on our system. Let's start with a hands-on to help you find and navigate those guides.
 
 
### Hands-on User Guide Cipher
 
This exercise is designed to help you understand which user guides are available and how to navigate to them. Book ciphers use numbers or instructions representing the positions of words in a text to navigate to words that form secret messages.
 
For example, if you were given (9,10,6,7,8) and pointed at the paragraph above, you could form a sentence by finding the 9th, 10th, 6th 7th and 8th word in that text.
 
You will use the section headings in the left menu bar of the OLCF Userguide at https://docs.olcf.ornl.gov plus the text counting clues given below each to navigate to words that allow you to decipher a tip that is helpful for new users.
 
Here are the rules:
 
1.  Count a sentence and its associated list of bullets or steps as one paragraph.
 
2.  Count hyphenated words as one word.
 
3.  Do not count bullets or list numbers when counting words.
 
Key: https://docs.olcf.ornl.gov, Look to the left menu bar. GO!
 
1. Systems> Frontier User Guide> Running Jobs> Batch Scripts;
    First word in the third paragraph.
 
2.  Systems> Frontier User Guide> Running Jobs> Process and Thread Mapping Examples;
    Tenth word in the second paragraph.
 
3.  Systems > Andes User guide>Running Jobs;
    Third paragraph, 4th step, fifth word.
 
4.  Data Storage and Transfers Guide > Alpine2 IBM Spectrum Scale Filesystem;
    First paragraph, third sentence. Look for the first comma in that sentence, grab the first word after that comma.
 
5. Data Storage and Transfers Guide > Summary of Storage Areas;
    Green “!Tip”Box, First sentence 10th word.
 
 
When you are done, raise your virtual hand.
 
## Authentication with RSA tokens
 
In an earlier section, we covered logging into Frontier or Odo using SSH and with your RSA token. Let's talk a bit more about what we're doing here.
 
We are using 2-factor authentication via user-selected PINs and RSA securID token. The numbers on the RSA securID token change every 30 seconds. Entering your PIN+tokencode is the only login method available. Using other methods (password, public key, etc) are not allowed.
 
### RSA terminology
* tokencode - the 6 digit number on your RSA token
* PIN - an alphanumeric string of 4-8 characters known only to you
* PASSCODE - your PIN followed by the current tokencode without any spaces
 
### Common Login Issues
 
SSH will not prompt you for your username, so make sure that when you SSH you are using the full `ssh <your username>@frontier.olcf.ornl.gov`.
 
Your RSA token might get out of sync with the server. So sometimes you might be prompted for 'next tokencode'
```
Enter PASSCODE:
Wait for the tokencode to change, then enter the new tokencode :
```
When this happens, enter only the tokencode your RSA token generates. Don't enter the PIN. In general, when it asks for PASSCODE, enter the PIN+tokencode. For any other case, the terminal will explicitly tell you what it wants you to do.
 
Sometimes you might encounter a message that looks like "Connection closed by <ip address>" after you correctly enter your PASSCODE. This usually indicates that your account no longer has access to the particular system you are trying to SSH to. Your account's access to systems is tied to your project. So when your project's access to a system expires, you lose access to that system.
 
 
If your PASSCODE has failed twice i.e. you are being prompted to enter your PASSCODE for the third time in a row, let the tokencode change before you try entering your PASSCODE again (to avoid getting locked out).
 
If you find that you keep entering the PASSCODE correctly but it fails to log you in, its possible you may have been locked out. Send an email to help@olcf.ornl.gov with the information on what you are seeing. If your account is locked, the OLCF Help Desk can unlock it for you.

## Storage at OLCF 

OLCF has a Network Files system (NFS) that you land on when you login. This is a small secure filesystem that is provisioned to hold your most important data. This is the best place for your executables and small important data. It is backed up. 

OLCF also has large parallel filesystems, Orion Luster for Frontier and Alpine2 GPFS for Summit. These are the filesystems that you should use to hold your large production data for simulation campaigns while you are running. They are not backed up and data older than 90 days are purged. 

OLCF storage systems have different areas designated for induvial user storage and project level storage that is controlled by the file permissions. Please make sure that data that is to be shared with multiple project members in in the project storage. This especially important as people leave your project. 

For details see our [Data Storage and Transfers Guide]( https://docs.olcf.ornl.gov/data/index.html).

Longer term storge will be available in OLCF’s nearline storge system called Kronos.  The target date for that late July. OLCF is currently in transitioning to Kronos from an archival storage system called HPSS. HPSS will become read-only in August. New projects should refrain from using it. 

See our [2024 Notable System Changes](https://docs.olcf.ornl.gov/systems/2024_olcf_system_changes.html)

## Hands on: Find your Storage Areas

Login to Frontier or Summit and go to your induvial user storage called “scratch”: 

Frontier (Orion) : 

```
cd /lustre/orion/[projid]/scratch/[userid]
ls
```

You can also do

```
cd $MEMBERWORK/[projid]
ls
```

Now let’s look at the project level storage, proj-shared:

```
cd /lustre/orion/[projid]/proj-shared/
ls

```

You can also do
```
cd $PROJWORK/[projid]/
ls
```

And for sharing between projects
```
cd /lustre/orion/[projid]/world-shared/
ls
```

You can also do
```
cd $WORLDWORK/[projid]
ls
```

For Summit (Alpine2) you can look up the paths here:
[Data Storage and Transfers Guide]( https://docs.olcf.ornl.gov/data/index.html).

However, the paths will be of the same form except the beginning will of each path will start with:

```
/gpfs/alpine2/[projid]/
```

And Alipne2 does not have the environment varaibles like $MEMEBERWORK” 


Summit (Alpine2) example for indivual storage:
```
cd /gpfs/alpine2/[projid]/scratch/[userid]
```
 
 
## Python on OLCF Systems
In high-performance computing, Python is heavily used to analyze scientific data on the system.
OLCF has a "Python on OLCF Systems" guide within the software guide. To find it, go to [https://docs.olcf.ornl.gov](https://docs.olcf.ornl.gov)> Software> Python on OLCF Systems. [Link](https://docs.olcf.ornl.gov/software/python/index.html#python-on-olcf-systems).
 
It tells you how to load the latest versions of python, manage your environment and run python on Summit, Frontier and Andes.
 
## Basic Python Hands-on
 
### Base Environment
 
Loading a module sets up a base python environment on each of our systems. Custom packages like numpy and scipy are not included in the base environment on most of our resources. We are going to use the "Python on OLCF Systems" guide for this exercise. Go to docs.olcf.ornl.gov> Software> [Python on OLCF Systems Base Environments](https://docs.olcf.ornl.gov/software/python/index.html#base-environment). 

Select the tab for the resource you are on and follow the instructions to list the packages. If you are using Odo follow the Frontier instructions.
 
For example, for Frontier/Odo you would do.
 
 
```
$ module load miniforge3/23.11.0
$ conda list
```
 
### Setting up a Custom Environment
 
Suppose you wanted to install the `numpy` package. If you do that in your base environment, it could get messy as you install more packages. It is a best practice to setup a custom environment that contains consistent versions of all the packages that you want to use for each particular project. This next hands-on walks you through setting up a custom environment that we will use later in the training. 
 
Open a new browser tab or window and direct it to [https://docs.olcf.ornl.gov/software/python/index.html#custom-environments](https://docs.olcf.ornl.gov/software/python/index.html#base-environment). In the tabs under "To create and activate an environment:" follow the instructions for the resource you are working on. If you are on Odo, follow the Frontier instructions.
 
For this exercise we will create a custom environment called *globus_env* in your /ccs/proj/<<your_project_id>>. If you are on Odo, you will use /ccsopen/proj/<<your_project_id>>.
 
For example on Frontier:
  
1. Load the module, if you have not done so already,
```
$ module load miniforge3/23.11.0
```
2 Create "globus_env" with Python version X.Y at the desired path
```
$ conda create -p /ccs/proj/<<your_project_id>>/globus_env python=3.10.13
```
3. Activate "globus_env"
```
$ source activate /ccs/proj/<<your_project_id>>/globus_env
```
 
Try it yourself. . . .
 
If you are on Frontier or Odo. It may print a message like this:

```
# To activate this environment, use
#
#     $ conda activate /ccsopen/proj/stf007/globus_env
#
# To deactivate an active environment, use
#
#     $ conda deactivate
```
 
Avoid using "conda activate" and "conda deactivate" as they add code blocks to your .bashrc file, causing compatibility issues when moving between different machines within OLCF with different versions of python. 
 
Use `source active` to activate your custom environments and `source deactivate` to deactivate them when you are done using them.
 
You must use the path to the custom environment to activate it. For example:
 
 
```
$ source activate /ccs/proj/<your_proeject_ID>/globus_env
```
We will use this environment in the next hands-on, but let's close it out cleanly to form good habits.
 
```
$ source deactivate
```
Ignore any warning that popup to use "conda activate".
 
 
There is more good information in the [Python on OLCF Systems]( https://docs.olcf.ornl.gov/software/python/index.html#base-environment) guide.
 


## Globus
 
* Globus is a fast and reliable way to move files between OLCF systems and between OLCF and other institutions.
* It has a convenient Web-interface at globus.org that you log into with a username and password.
* Transfers are done by activating “Collections” which are portals in to the OLCF's file systems and to those of participating institutions.
* Globus is the recommended way to move files between OLCF systems and between OLCF and exterior systems.
 
For this exercise we will setup your globus.org username and password. You can skip this if you have a globus ID.

Note: Globus is not controlled by OLCF and its help and login pages and option change without warning. This hands-on is based on Globus pages from 05-02-24. Even if the specific Globus pages chanage, this tutorial should be close to what is needed to get a globus username and password.
 
### Hands-on GlobusID
 
1. Open a browser and direct it to globusid.org.
2. Select "create GlobusID" and follow the instructions
3. Remember your globusID and password someplace safe.
 
Now try to log in: 

1. Go to globus.org and click "Login"
  
2.  Find the "use Globus ID" link and use your GlobusID to login.  The Oak Ridge National Laboratory login is only for ORNL staff.
3. You should see the Globus "File Manager" when you are logged in.
 
### Activating a Globus Collection
 
Activating the OLCF Globus Collection is done using your OLCF username and Token Passcode. Think of it ask logging in to an OLCF filesystem.

Collections stay activated for three days so you don’t need to enter your credentials for each transfer and you can run a transfer workflow during a simulation.
  
The OLCF Moderate Collection is called “OLCF DTN (Globus 5)”. 

If you are on Odo, you are in the OLCF Open enclave and its Collection is called "NCCS Open DTN (Globus 5)" and is a portal to the open NFS and GPFS filesystems.
 
This assumes that you have logged in using steps like those in the Hands-On Globus-ID exercise.  
 
1.	Type "OLCF" in the Collections bar. A list of options for OLCF will form below, select the “OLCF DTN (Globus 5)” Collection. (If you are doing this training on Odo, look for NCCS Open DTN (globus5) instead.)

2.	If Globus pings you to associate your Globus ID with OCLF credentials, follow the instructions that it gives.

3.	 When prompted, sign in with your OLCF UserName and PIN+ PASSCODE. (If you are doing this from Odo, use the Username and XCAMS password to login)
 
You should see the files that you have in /ccs/home/<<your_user_ID>>>
 
You can reach both Orion Luster and Alpine2 GPFS from the “OLCF DTN (Globus 5)” Collection. You do so by entering the path to them in the Path bar.
 
* Summit users: Path to Alpine2 `/gpfs/alpine2/<your_project_ID>>`
 
* Frontier users: Path to Orion `/gpfs/orion/<<your_project_ID>>`
 
* Odo users: Path to wolf2 `/gpfs/wolf2/olcf/<<your_project_ID>>`
 
4.	Enter the path for the resource you are on.
 
Either way you will see three directors list in the file manager:

* scratch - personal workspace on the parallel file system purged every 90 days.
* proj-shared - Workspace on the parallel file system for your project 
* world-shared- Workspace on the parallel file system where files can be shared between projects.
 
5.	You can click on those spaces to see what's in them from the file manager.

If you want to setup a personal Globus Collection on your laptop, follow these instructions: https://www.globus.org/globus-connect-personal.


 
## Globus Transfer

The Department of Energy Energy Sciences Network ( ESnet) has deployed anonymous read-only GridFTP servers for data transfer testing purposes. We are going to use one of those, called "ESnet Denver DTN (Anonymous read only testing)" and its testfiles to do the next two exercises because everyone can get to them from globus.

Let's move a test file from an ESnet test collection into our scratch workspace.

1. Go to the browser tab that has the Globus file manager in it and find the panels options in the upper right.

2. Click on the picture of the double panel. After that you should have a panels on the left and right that each have collections and path bars.

3. Enter "ESnet Denver DTN (Anonymous read only testing)" in the left collection bar.

4. You will see a folders with different sized files and folders listed. We are going to transfer the 10MB file called `10M.dat`.  

5. In the right collections bar enter the  “OLCF DTN (Globus 5)”, then either enter the path to your scratch directory `/gpfs/orion/<<your_project_ID>>/scratch/<<your_user_ID>>’ in the path bar or navigate to it by clicking on the folders in the File manager.    

6. To move the file "10M.dat" from the "ESnet Denver DTN (Anonymous read only testing)" to your OLCF parallel file system scratch area, simply drag and drop "10M.dat" from panel to panel. You can also select "10M.dat" and click on the arrows to move it.
 
Globus will notify you when the transfer is complete. 

If you are a NERSC user, you can use their collections too, you just need to activate the collection with your NERSC credentials. 

###A few tips for using Globus

1. If you are moving files from one parallel filesystem to another, it is better to move many files, at once, for example, by moving a folder.  Globus will use the parallel systems to move the files faster. 

2. If you are moving files to or from a single disk it will not help the speed to move them in folders. 

3. OLCF's HPSS is retiring in August, but if you are moving files to an HPSS at another center, please tar the files first. HPSS is designed to handle large files better than many small files, and many small files can fill up the cache and block performance for all users.
 
### GlobusCLI
 
We realize that not everyone will want to use a GUI interface for moving data. Globus offers a few APIs. We will leave it to the use to find examples in Globus's helpful users guides:
 
https://docs.globus.org/cli/
https://docs.globus.org/cli/quickstart/
 
However, users must install Globus CLI themselves to use it, and that is best done within a custom python environment. So, our next hands-on is an example of how to do that.
 
In a previous example we setup a custom environment,`/ccs/proj/<your_proeject_ID>/globus_env` in  the non-purged project-centric storage area on the NFS filesystem. Let's start by reactivating that.
 
```
$ Module load miniforge3
$ source activate /ccs/proj/<your_proeject_ID>/globus_env 
```
 
Globus recommends using pip to install GlobusCLI
 
So next let's do that:
 
```
(/ccs/proj/<<your_proj_ID/globus_env) [<<your_User_ID>>@login1.odo ~]$ pip install globus-cli
 
Collecting globus-cli
  Downloading globus_cli-3.28.2-py3-none-any.whl.metadata (2.4 kB)
Collecting globus-sdk==3.41.0 (from globus-cli)
  Downloading globus_sdk-3.41.0-py3-none-any.whl.metadata (3.3 kB)
Collecting click<9,>=8.1.4 (from globus-cli)
  Downloading click-8.1.7-py3-none-any.whl.metadata (3.0 kB)
Collecting jmespath==1.0.1 (from globus-cli)
  Downloading jmespath-1.0.1-py3-none-any.whl.metadata (7.6 kB)
Collecting packaging>=17.0 (from globus-cli)
  Downloading packaging-24.0-py3-none-any.whl.metadata (3.2 kB)
Collecting requests<3.0.0,>=2.19.1 (from globus-cli)
.  .  .
 
.  .  .
Downloading pycparser-2.22-py3-none-any.whl (117 kB)
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 117.6/117.6 kB 11.2 MB/s eta 0:00:00
Installing collected packages: urllib3, typing-extensions, pyjwt, pycparser, packaging, jmespath, idna, click, charset-normalizer, certifi, requests, cffi, cryptography, globus-sdk, globus-cli
Successfully installed certifi-2024.2.2 cffi-1.16.0 charset-normalizer-3.3.2 click-8.1.7 cryptography-42.0.5 globus-cli-3.28.2 globus-sdk-3.41.0 idna-3.7 jmespath-1.0.1 packaging-24.0 pycparser-2.22 pyjwt-2.8.0 requests-2.31.0 typing-extensions-4.11.0 urllib3-2.2.1
 
```
You should now have globus cli in an area where all the members of your project can use it. 
 
If you want test do the globus login and follow the instructions given:
 
For example, here is the command from my globus_env on Odo:
 
 
```
(/ccs/proj/stf007/globus_env) [nk8@login1.odo ~]$ globus login
 
```
 
It will give you a link and tell you to paste it in your browser. That will lead you to the same login we did for your globus ID from the globus web GUI.
  
You will also have to activate collections from the GUI. But the collections stay active for three days before you need to re-authenticate, so you can still  
run a workflow with globus using the scripts.
 


For more data transfer tips see: [OCLF Data transfer Tutorial]( https://www.olcf.ornl.gov/wp-content/uploads/Data-Transfer.pdf)

And the 
[OLCF Data Storage and Transfers Guide]( https://docs.olcf.ornl.gov/data/index.html#data-storage-and-transfers)

 
## Finding and Building Software
 
(the following section applies to Odo as well, so you can follow along if you're on Odo)
 
Frontier supports a large number of users from a wide range of scientific disciplines. Different users have needs for different users. Some users might need to use different versions of the same software. In order to accommodate this, Frontier uses Lmod. Lmod manages software installed on Frontier in the form of 'modules'. You can get access to a specific software or package or library you need by 'loading' the specific module (provided it is available on Frontier).
 
 
For example, if you want to use the `hipcc` compiler which is part of AMD's ROCm software stack, you need to first load the `amd-mixed` or the `rocm` module. The command is the same as what you did earlier to load miniforge
 
```
$ hipcc --version
If 'hipcc' is not a typo you can use command-not-found to lookup the package that contains it, like this:
    cnf hipcc
$ module load amd-mixed
$ hipcc --version
HIP version: 5.3.22061-e8e78f1a
AMD clang version 15.0.0 (https://github.com/RadeonOpenCompute/llvm-project roc-5.3.0 22362 3cf23f77f8208174a2ee7c616f4be23674d7b081)
Target: x86_64-unknown-linux-gnu
Thread model: posix
InstalledDir: /opt/rocm-5.3.0/llvm/bin
```
 
If you want to use a specific version of the ROCm software stack, you can check which versions are available by running `module spider amd-mixed`.
 
```
$ module spider amd-mixed
 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  amd-mixed:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
     Versions:
        amd-mixed/4.5.2
        amd-mixed/5.1.0
        amd-mixed/5.2.0
        amd-mixed/5.3.0
        amd-mixed/5.4.0
        amd-mixed/5.4.3
        amd-mixed/5.5.1
        amd-mixed/5.6.0
        amd-mixed/5.7.0
        amd-mixed/5.7.1
 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  For detailed information about a specific "amd-mixed" package (including how to load the modules) use the module's full name.
  Note that names that have a trailing (E) are extensions provided by other modules.
  For example:
 
     $ module spider amd-mixed/5.7.1
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
```
You can see the full list of modules available to load by simply executing `module spider` without a module name given.
 
```
$ module spider
 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
The following is a list of the modules and extensions currently available:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  DefApps: DefApps/default
 
  PrgEnv-amd: PrgEnv-amd/8.3.3, PrgEnv-amd/8.4.0
 
  PrgEnv-cray: PrgEnv-cray/8.3.3, PrgEnv-cray/8.4.0
 
  PrgEnv-cray-amd: PrgEnv-cray-amd/8.3.3, PrgEnv-cray-amd/8.4.0
 
  PrgEnv-gnu: PrgEnv-gnu/8.3.3, PrgEnv-gnu/8.4.0
 
  PrgEnv-gnu-amd: PrgEnv-gnu-amd/8.3.3, PrgEnv-gnu-amd/8.4.0
 
  amd: amd/4.5.2, amd/5.1.0, amd/5.2.0, amd/5.3.0, amd/5.4.0, amd/5.4.3, amd/5.5.1, amd/5.6.0, amd/5.7.0, amd/5.7.1
 
<truncated for space>
```
 
And you can load a specific version of a module like amd-mixed 5.4.0 by specifying the version number in the `module load` command like so:
 
```
$ module load amd-mixed/5.4.0
```
 
If a specific version number is not specified, it will load a system defined default version (in the case of amd-mixed, the default version loaded is 5.3.0).
 
 
`module load` does a few things, chief among which is it updates some environment variables that the OS uses to look for software or libraries. You can see information about a module and a summary of what changes are made when you execute a `module show` operation.
 
```
$ module show amd-mixed
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   /opt/cray/pe/lmod/modulefiles/mix_compilers/amd-mixed/5.3.0.lua:
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
family("amd_compiler")
conflict("amd")
help([[5.3.0
/opt/rocm-5.3.0
This modulefile defines the system paths and environment
variables needed to use the AMD Optimizing C/C++ Compiler.
 
===================================================================
To see AMD/5.3.0 release information,
  visit https://rocmdocs.amd.com/en/latest
===================================================================
 
To make this the default version, execute:
  /opt/admin-pe/set_default_craypkg/set_default_amd_5.3.0
 
]])
whatis("Defines the system paths and environment variables needed for the AMD LLVM Compiling Environment.")
prepend_path("PATH","/opt/rocm-5.3.0/bin")
prepend_path("LIBRARY_PATH","/opt/rocm-5.3.0/llvm/lib")
prepend_path("LD_LIBRARY_PATH","/opt/rocm-5.3.0/llvm/lib")
prepend_path("C_INCLUDE_PATH","/opt/rocm-5.3.0/llvm/include")
prepend_path("CPLUS_INCLUDE_PATH","/opt/rocm-5.3.0/llvm/include")
prepend_path("CMAKE_PREFIX_PATH","/opt/rocm-5.3.0")
prepend_path("CMAKE_PREFIX_PATH","/opt/rocm-5.3.0/hip")
setenv("ROCM_COMPILER_PATH","/opt/rocm-5.3.0/llvm")
setenv("ROCM_COMPILER_VERSION","5.3.0")
setenv("CRAY_AMD_COMPILER_PREFIX","/opt/rocm-5.3.0")
setenv("CRAY_AMD_COMPILER_VERSION","5.3.0")
setenv("ROCM_PATH","/opt/rocm-5.3.0")
setenv("HIP_PATH","/opt/rocm-5.3.0/hip")
setenv("HIP_LIB_PATH","/opt/rocm-5.3.0/lib")
setenv("HSA_PATH","/opt/rocm-5.3.0/hsa")
prepend_path("CMAKE_PREFIX_PATH","/opt/rocm-5.3.0")
prepend_path("CMAKE_PREFIX_PATH","/opt/rocm-5.3.0/hip")
prepend_path("LD_LIBRARY_PATH","/opt/rocm-5.3.0/lib")
prepend_path("LD_LIBRARY_PATH","/opt/rocm-5.3.0/lib64")
prepend_path("LD_LIBRARY_PATH","/opt/rocm-5.3.0/hsa/lib")
```
 
 
At anytime you can check the modules that are currently loaded by running `module list`
 
```
$ module list
 
Currently Loaded Modules:
  1) craype-x86-trento    3) craype-network-ofi       5) xpmem/2.6.2-2.5_2.22__gd067c3f.shasta   7) cce/15.0.0      9) cray-dsmml/0.2.2   11) cray-libsci/22.12.1.1  13) DefApps/default
  2) libfabric/1.15.2.0   4) perftools-base/22.12.0   6) cray-pmi/6.1.8                          8) craype/2.7.19  10) cray-mpich/8.1.23  12) PrgEnv-cray/8.3.3      14) amd-mixed/5.3.0
 
```
 
Now it might seem strange there are a number of modules in the list in addition to the `amd-mixed` module you loaded. This is because Frontier loads a default set of modules every time you log in. You will also notice that a number of these default modules start with `cray`. Frontier is an HPE Cray system, and so several software libraries are provided by the Cray software team that are optimized for use on Frontier.
 
One of the modules in the above list is `PrgEnv-cray`. This means that the Cray Programming Environment. A Programming Environment is a collection of libraries along with a compiler that are all loaded together. `PrgEnv-cray` loads the Cray Compiling Environment which is the set of C, C++, and Fortran compilers along with libraries compiled with those compilers. When this programming environment is loaded, the Cray compilers are available for use. Also available are PrgEnv-gnu and PrgEnv-amd, which loads the GNU and AMD compilers respectively, along with reloading any libraries to load the libraries compiled with the currently loaded compiler.
 
For example, if you load PrgEnv-gnu, you will see the following output.
 
```
$ module load PrgEnv-gnu
 
Lmod is automatically replacing "cce/15.0.0" with "gcc/12.2.0".
 
 
Lmod is automatically replacing "PrgEnv-cray/8.3.3" with "PrgEnv-gnu/8.3.3".
 
 
Due to MODULEPATH changes, the following have been reloaded:
  1) cray-mpich/8.1.23
```
 
Here's a list of the useful commands we've seen so far:
`module load` - load a module so that it becomes available to use
`module show` - show more information about a particular module
`module list` - show list of currently loaded modules
`module spider` - show list of modules and their versions, or if a module name is specified, show the versions of those modules that are available to load
 
Building software:
 
To compile your C, C++, or Fortran code, you will not invoke the compiler command directly but instead you will invoke the Cray provided compiler wrappers.
 
For example, say you had PrgEnv-gnu loaded because you wanted to use the `gcc` compiler. Instead of using the `gcc` command directly, you will use the compiler wrapper command `cc`.
 
```
$ cc -o hello hello.c
```
 
For C code, you will use the `cc` compiler wrapper. For C++, you will use the `CC` compiler wrapper. And for Fortran you will use `ftn`. This applies for any programming environment you may be using.  The compiler wrapper automatically includes the necessary header files and libraries needed for MPI so you don't have to explicitly link the MPI libraries. There are nuances to this that aren't covered here, such as when you're compiling for both MPI and GPU functionality. See more information about compiling in [the Frontier documentation](https://docs.olcf.ornl.gov/systems/frontier_user_guide.html#compiling).
 
You can run `cc -craype-verbose` to get a full picture of what the compiler wrapper is doing when compiling.
 
## Training Opportunities
 
- Keep an eye out for upcoming trainings on our [Training Calendar](https://www.olcf.ornl.gov/for-users/training/training-calendar)
- Missed a training? All our trainings are recorded and are listed in the [Training Archive](https://docs.olcf.ornl.gov/training/training_archive.html)
- tell us what kinds of training you would like to see
 
## Getting Help
 
If you're stuck, the OLCF Help Desk is here to help! You can email us at help@olcf.ornl.gov 
