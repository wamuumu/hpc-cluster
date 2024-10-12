#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        int sum = 0;
        int i;
        for (i = 1; i < comm_sz; i++) {
            int received;
            MPI_Recv(&received, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += received;
        }
        printf("Process %d received: %d\n", my_rank, sum);
        fflush(stdout);
    } else {
        int number = my_rank * 10;
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process %d sent: %d\n", my_rank, number);
        fflush(stdout);
    }

    MPI_Finalize();

    return 0;
}