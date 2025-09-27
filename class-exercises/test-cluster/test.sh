#!/bin/bash

#PBS -l select=1:ncpus=1:mem=2gb

#set max execution time
#PBS -l -walltime=0:00:10

#set execution queue
#PBS -q short_cpuQ

sleep 60
ls -lrt
echo "hostname: " && hostname
