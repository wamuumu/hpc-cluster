#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int globaldata[comm_sz];

    MPI_Gather(&my_rank, 1, MPI_INT, globaldata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(my_rank == 0) {
        printf("[%d]: ", my_rank);
        int i;
        for(i = 0; i < comm_sz; i++) {
            printf("%d ", globaldata[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}