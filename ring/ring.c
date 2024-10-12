#include <mpi.h>
#include <stdio.h>
#include <string.h>

const int MAX_STRING = 100;

int main(int argc, char** argv) {

    char message[MAX_STRING];
    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        sprintf(message, "Ring%d", my_rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, (my_rank + 1) % comm_sz, 0, MPI_COMM_WORLD);
        printf("Process %d sent: %s\n", my_rank, message);
        fflush(stdout);

        MPI_Recv(message, MAX_STRING, MPI_CHAR, comm_sz - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received: %s\n", my_rank, message);
        fflush(stdout);
    } else {
        MPI_Recv(message, MAX_STRING, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received: %s\n", my_rank, message);
        fflush(stdout);

        sprintf(message, "Ring%d", my_rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, (my_rank + 1) % comm_sz, 0, MPI_COMM_WORLD);
        printf("Process %d sent: %s\n", my_rank, message);
        fflush(stdout);
    }

    MPI_Finalize();

    return 0;
}