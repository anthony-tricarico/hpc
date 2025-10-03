/* Implement a "ping pong" using send & receive.
 * Two processes one send and one receive each.*/
#include <stdio.h>
#include <mpi.h>
#include <ctype.h>

#define TAG_DATA 0
#define TAG_STOP 1

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
            printf("Enter an integer to send to the other process: \n");
            scanf("%d", &data);
            getchar();

        /* loop continues indefinitely until explictly asked to */
        while (1) {
            printf("Do you want to continue sending the message? (y/n): ");
            scanf(" %c", &c);
            c = tolower(c);

            if (c == 'y') {
                /* Send message to process 1 */
                MPI_Send(&data, 1, MPI_INT, 1, TAG_DATA, MPI_COMM_WORLD);
                printf("Process %d: Message sent\n", rnk);
                /* Receive message from process 1 */
                MPI_Recv(&data, 1, MPI_INT, 1, TAG_DATA, MPI_COMM_WORLD, &status);
                printf("Process %d: Message received\n", rnk);
            } else {
                MPI_Send(&data, 1, MPI_INT, 1, TAG_STOP, MPI_COMM_WORLD);
                break;
                
            }
        }
    } else {
         /* Receive message from process 0 */
       while (1) { 
            MPI_Recv(&data, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == TAG_STOP) break;

            printf("Process %d: Message received\n", rnk);
            /* Send message to process 0 */
            MPI_Send(&data, 1, MPI_INT, 0, TAG_DATA, MPI_COMM_WORLD);
            printf("Process %d: Message sent\n", rnk);
        }
    }

    #endif
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
