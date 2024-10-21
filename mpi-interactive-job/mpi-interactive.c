#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

    // [qsub -I job] to run this code in interactive mode
    // qsub -I access to the compute node

    // Once inside the computing node, just navigate to the folder and execute the code with mpirun (before load the module)

    // Usage example:
    // qsub -I -l select=1:ncpus=4:mem=2gb,walltime=0:05:00 -q short_cpuQ
    // qsub -I file.sh (containing the PBS directives)
    // qstat -f $PBS_JOBID (to check the job details)

    int m, n;
    if (my_rank == 0) {
        printf("Enter two values: ");
        scanf("%d %d", &m, &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("[%d]: n = %d, m = %d\n", my_rank, n, m);

    MPI_Finalize();

    return 0;
}