#!/bin/bash
#PBS -l select=2:ncpus=1:mem=2gb -l place=pack
# set max execution time
#PBS -l walltime=0:05:00
# imposta la coda di esecuzione
#PBS -q short_cpuQ
module load mpich-3.2
cd ./hpc-cluster/p2p-communication
mpirun.actual -n 2 ./p2pbc 