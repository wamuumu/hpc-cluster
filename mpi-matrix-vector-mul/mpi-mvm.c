#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    int comm_sz; // Number of processes
    int my_rank; // Process rank
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

    int m, n;

    int *matrix;
    int *vector;
    int *result;

    if (my_rank == 0) {
        /*printf("Enter rows and cols: ");
        scanf("%d %d", &m, &n);

        vector = (int *)malloc(n * sizeof(int)); // n elements
        result = (int *)malloc(m * sizeof(int)); // same size as rows
        matrix = (int *)malloc(m * n * sizeof(int)); // m rows, n columns
        
        int i, j;
        printf("Enter matrix: \n");
        for (i = 0; i < m; i++) {
            printf("Row %d\n", (i+1));
            for (j = 0; j < n; j++) {
                printf("Col %d: ", (j+1));
                scanf("%d", &matrix[i*n+j]);
            }
        }

        printf("Enter vector: \n");
        for (i = 0; i < n; i++) {
            printf("Element %d: ", (i+1));
            scanf("%d", &vector[i]);
        }*/

        m = comm_sz;
        n = 2;
        
        vector = (int *)malloc(n * sizeof(int)); // n elements
        result = (int *)malloc(m * sizeof(int)); // same size as rows
        matrix = (int *)malloc(m * n * sizeof(int)); // m rows, n columns
        
        int i, j;
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                matrix[i * n + j] = i + 1;
            }
        }

        printf("Initial matrix: \n");
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                printf("%d ", matrix[i * n + j]);
            }
            printf("\n");
        }

        for (i = 0; i < n; i++) {
            vector[i] = i + 1;
        }

        printf("Initial vector: \n");
        for (i = 0; i < n; i++) {
            printf("%d ", vector[i]);
        }

        printf("\n\n");
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast the number of rows
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast the number of cols
    
    if (my_rank != 0)
        vector = (int *)malloc(n * sizeof(int)); // Allocate memory for the vector

    MPI_Bcast(vector, n, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast the vector

    printf("[%d]: m = %d, n = %d\n", my_rank, m, n);
    printf("[%d]: ", my_rank);

    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    int *local_row = (int *)malloc(n * sizeof(int));
    MPI_Scatter(matrix, n, MPI_INT, local_row, n, MPI_INT, 0, MPI_COMM_WORLD); // Scatter the matrix

    printf("[%d]: ", my_rank);
    for (i = 0; i < n; i++) {
        printf("%d ", local_row[i]);
    }
    printf("\n");

    int local_i;
    int local_result = 0;
    
    for (local_i = 0; local_i < n; local_i++) {
        local_result += local_row[local_i] * vector[local_i];
    }

    MPI_Gather(&local_result, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD); // Gather the results

    if (my_rank == 0) {
        printf("\nResult: ");
        int i;
        for (i = 0; i < m; i++) {
            printf("%d ", result[i]);
        }
    }
    printf("\n");

    MPI_Finalize();

    return 0;
}