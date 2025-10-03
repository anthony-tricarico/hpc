/* Implement a "ping pong" using send & receive.
 * Two processes one send and one receive each.*/
#include <stdio.h>
#include <mpi.h>
#include <ctype.h>

#define STOP_TAG 0
#define MESSAGE_TAG 1

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rnk, n_prcs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &n_prcs);

    MPI_Status status;
    int data;
    char c = 'y';

    #ifdef TWO_PROCS
    /* This process will collect user input and send it to the other process and then
     * get it back from the other process */
    if (rnk == 0) {
        /* collect user input */
        printf("Insert integer message to pass between processes: ");
        fflush(stdout);
        scanf("%d", &data);
        /* send messages continuously until stopped */
        while (1) {
            printf("Continue? (y/n): ");
            fflush(stdout);
            scanf(" %c", &c);
            
            if (c == 'y') {
                /* sends message to process 1 */
                MPI_Send(&data, 1, MPI_INT, 1, MESSAGE_TAG, MPI_COMM_WORLD);
                printf("Process: %d sent message: %d\n", rnk, data);
                fflush(stdout);

                /* receives message from process 1 */
                MPI_Recv(&data, 1, MPI_INT, 1, MESSAGE_TAG, MPI_COMM_WORLD, &status);
                printf("Process: %d received message: %d\n", rnk, data);
                fflush(stdout);
            } else {
                MPI_Send(&data, 1, MPI_INT, 1, STOP_TAG, MPI_COMM_WORLD);
                MPI_Recv(&data, 1, MPI_INT, 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                break;
            }
        }

    } else {
        while (1) {
            MPI_Recv(&data, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (status.MPI_TAG == STOP_TAG) {
                MPI_Recv(&data, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                MPI_Send(&data, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD);
                printf("Process %d received STOP signal.\n", rnk);
                fflush(stdout);
                break;
            }
            printf("Process %d received message: %d\n", rnk, data);
            fflush(stdout);

            MPI_Send(&data, 1, MPI_INT, 0, MESSAGE_TAG, MPI_COMM_WORLD);
            printf("Process %d sent message: %d\n", rnk, data);
            fflush(stdout);
        }
    }


    #endif
    // MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
