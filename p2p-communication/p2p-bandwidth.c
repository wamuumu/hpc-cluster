#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {

    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (comm_sz != 2) {
        fprintf(stderr, "World size must be two for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    double start_time, end_time, elapsed_time;
    double bandwidth;

    if (my_rank == 0) {
        printf("n\ttime (sec)\trate (MB/sec)\n");
    }
    
    int i;
    int iterations = 20;
    for (i = 0; i < iterations; i++) {

        int message_size = pow(2, i);
        char* message = (char*) malloc(message_size * sizeof(char));
        
        if (my_rank == 0) {
            
            start_time = MPI_Wtime();
            MPI_Send(message, message_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(message, message_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            end_time = MPI_Wtime();

            // Calculate the elapsed time (seconds)
            elapsed_time = end_time - start_time;

            // Calculate the bandwidth (MB/second)
            bandwidth = (message_size / pow(1024, 2)) / elapsed_time;

            // format the output in three columns: message size, elapsed time, bandwidth
            printf("%d\t%f\t%f\n", message_size, elapsed_time, bandwidth);
        } else {
            MPI_Recv(message, message_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(message, message_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }

        free(message);
    }

    MPI_Finalize();

    return 0;
}