/* Implement a "ping pong" using send & receive.
 * Two processes one send and one receive each.*/
#include <stdio.h>
#include <mpi.h>
#include <ctype.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rnk, n_prcs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &n_prcs);

    MPI_Status status;
    int data;
    char c = 'y';

    #ifdef TWO_PROCS
    if (rnk == 0) {
        int data = 5;
        int cycle = 0;
        while (c != 'n') {
            MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Send(&c, 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
            printf("Data in process %d is: %d\n", rnk, data);
            data++;
            cycle++;
            printf("Do you want to continue? (y/n)\nCurrent iteration %d\n", cycle);
            c = tolower(getchar());
            // getchar();
        }
    } else {
        while (c != 'n') {
            MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&c, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
            MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            printf("Data in process %d is: %d\n", rnk, data);
        }
    }
    #endif
    MPI_Finalize();
    return 0;
}
