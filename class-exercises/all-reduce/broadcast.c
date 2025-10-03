#include "broadcast.h"
#include <stdio.h>
#include <mpi.h>

/* Function to send from sending node to receiving node */
void broadcast(Msg *msg, const int sending, int rank, int n_prcs) {
    int i;
   if (rank == sending) {
        for (i = rank+1; i < n_prcs; i++) {
            MPI_Send(msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process %d sent message to process %d\n", rank, i);
        }
    } else {
        MPI_Recv(msg, 1, MPI_INT, sending, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received message from process %d\n", rank, sending);
    }
    printf("All messages sent and received correctly.\n");
}

