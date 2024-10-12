#!/bin/bash
#PBS -l select=1:ncpus=4:mem=2gb
# set max execution time
#PBS -l walltime=0:05:00
# imposta la coda di esecuzione
#PBS -q short_cpuQ
module load mpich-3.2

# esegue il programma partendo dalla home directory, pertanto specifica percorso completo 
# oppure cambia la directory di lavoro con cd
# cd ./hpc-cluster/mpi-hello-world
mpirun.actual -n 4 ./hpc-cluster/mpi-hello-world/mpi-hello