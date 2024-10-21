#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int globaldata[comm_sz];
    int localdata;

    if (my_rank == 0) {        

        printf("Processor %d has data: ", my_rank);

        int i;
        for (i = 0; i < comm_sz; i++) {
            globaldata[i] = i;
            printf("%d ", globaldata[i]);
        }

        printf("\n");
    }

    // Send 1 integer to each processor (root included) from the root globaldata
    MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Processor %d has data %d\n", my_rank, localdata);

    MPI_Finalize();

    return 0;
}