#!/bin/bash
#PBS -l select=1:ncpus=1:mem=2gb
# set max execution time
#PBS -l walltime=0:01:00
# define the queue
#PBS -q short_cpuQ
echo "hostname: " && hostname
