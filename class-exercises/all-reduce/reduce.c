#include <stdio.h>
#include <mpi.h>
#include "reduce.h"
#include "broadcast.h"

Msg reduce(Msg *msg, int receiving, int rank, int n_prcs) {
    if (rank == receiving) {
        Msg sum = 0;
        for (int i = 1; i < n_prcs; i++) {
            MPI_Recv(msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            sum += *msg;
            printf("Process %d received message from process %d\n", receiving, i);
        }
        return sum;
    } else {
        MPI_Send(msg, 1, MPI_INT, receiving, 0, MPI_COMM_WORLD);
        printf("Process %d sent message to process %d\n", rank, receiving);
    }
        
}
