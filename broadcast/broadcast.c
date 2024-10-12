#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        int number = 5;
        int i;
        for (i = 1; i < comm_sz; i++) {
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process %d sent: %d\n", my_rank, number);
            fflush(stdout);
        }
    } else {
        int received;
        MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received: %d\n", my_rank, received);
        fflush(stdout);
    }

    MPI_Finalize();

    return 0;
}