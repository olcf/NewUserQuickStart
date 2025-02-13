#!/bin/bash
#SBATCH -A <YOUR_PROJECT_ID>
#SBATCH -J mpi4py
#SBATCH -o %x-%j.out
#SBATCH -t 0:10:00
#SBATCH -p batch
#SBATCH -N 1

unset SLURM_EXPORT_ENV

date

module load PrgEnv-gnu
module load miniforge3

source activate /ccs/proj/<your_project_id>/<your_user_id>/.conda/frontier/mpi4py_env

srun -n42 python3 -u hello_mpi.py
