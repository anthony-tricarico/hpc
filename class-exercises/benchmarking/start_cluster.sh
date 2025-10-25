#!/bin/bash
#PBS -l select=1:ncpus=2:mem=2gb -l place=pack:excl
# set max execution time
#PBS -l walltime=0:01:00
# set execution queue
#PBS -q short_cpuQ
cd $PBS_O_WORKDIR
module load mpich-3.2
mpirun.actual -n 2 ./benchmark
