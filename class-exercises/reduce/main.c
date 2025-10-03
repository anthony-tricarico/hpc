#include <stdio.h>
#include <mpi.h>

#define GATHERING_PRC 0

typedef int Item;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rnk, n_prcs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &n_prcs);

    MPI_Status status;
    Item msg;

    if (rnk == GATHERING_PRC) {
        /* Request input and initialize message */
        printf("Initialize integer variable, input a value: ");
        scanf("%d", &msg);
        /* Send messages to the following node */
        MPI_Send(&msg, 1, MPI_INT, rnk + 1, 0, MPI_COMM_WORLD);
        /* Initialize sum variable to 0 */
        int sum = 0;
        /* Iterate over all other processes to retrieve data from those */
        for (int i = GATHERING_PRC + 1; i < n_prcs; i++) {
            MPI_Recv(&msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            sum += msg;
        }
        printf("The final value is %d\n", sum);
    } else {
        /* Receive message from previous rank */
        MPI_Recv(&msg, 1, MPI_INT, rnk - 1, 0, MPI_COMM_WORLD, &status);
        /* Increase msg by one */
        msg++;
        /* Checks that the process is not the last one and if it is not it sends to the next process */
        if (rnk != n_prcs - 1) 
            MPI_Send(&msg, 1, MPI_INT, rnk + 1, 0, MPI_COMM_WORLD);
        /* Anyway all the data must go to the GATHERING_PRC to be summed */
        MPI_Send(&msg, 1, MPI_INT, GATHERING_PRC, 0, MPI_COMM_WORLD);
    }

    return 0;
}
