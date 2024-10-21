#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int buf = -1;
    printf("[%d]: Before Bcast, buf is %d\n", my_rank, buf);

    if (my_rank == 0) {
        buf = my_rank;
    }

    MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("[%d]: After Bcast, buf is %d\n", my_rank, buf);

    MPI_Finalize();

    return 0;
}