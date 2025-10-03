/* Implement a closed ring with 4 processes executing in parallel. 
 * A closed ring is made of 4 nodes (in this case) each receiving and passing data to the next node 
 * with the last node passing back the message to the first node */

#include <stdio.h>
#include <stdbool.h>
#include <mpi.h>

typedef int Item;

void logging(int rnk, Item msg, bool receiving) {
    if (receiving)
        printf("Process %d received message: %d\n", rnk, msg); 
    else
        printf("Process %d sent message: %d\n", rnk, msg); 
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rnk, n_prcs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &n_prcs);

    Item msg;
    MPI_Status status;

    /* Branch executed by process 0 (usually used to collect input) */
    if (rnk == 0) {
        printf("Insert the integer to pass across processes: ");
        scanf("%d", &msg);

        MPI_Send(&msg, 1, MPI_INT, rnk + 1, 0, MPI_COMM_WORLD);
        logging(rnk, msg, false);
        MPI_Recv(&msg, 1, MPI_INT, n_prcs - 1, 0, MPI_COMM_WORLD, &status);
        logging(rnk, msg, true);
    } else if (rnk == n_prcs - 1) {
            MPI_Recv(&msg, 1, MPI_INT, rnk - 1, 0, MPI_COMM_WORLD, &status);
            logging(rnk, msg, true);
            MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            logging(rnk, msg, false);
        } else {

        MPI_Recv(&msg, 1, MPI_INT, rnk - 1, 0, MPI_COMM_WORLD, &status);
        logging(rnk, msg, true);
        MPI_Send(&msg, 1, MPI_INT, rnk + 1, 0, MPI_COMM_WORLD);
        logging(rnk, msg, false);
    }

    MPI_Finalize();

    return 0;
}
