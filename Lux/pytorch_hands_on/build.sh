#!/bin/bash

# Pip and conda caches can quickly fill up a home directory quota.
# You can avoid this by pointing the cache directory to somewhere on Orion
# E.g., export PIP_CACHE_DIR="/lustre/orion/projid/userid/cache_dir"
# export CONDA_PKGS_DIRS="/lustre/orion/projid/userid/cache_dir"

module load rocm/7.2.4
module load miniforge3/26.3.2-3

conda create -p $(pwd)/lux_torch_env python=3.12 -y

pip install torch torchvision --index-url https://download.pytorch.org/whl/rocm7.2 



