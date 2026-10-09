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

### Lmod

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
