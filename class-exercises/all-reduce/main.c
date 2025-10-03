#include "broadcast.h"
#include "reduce.h"
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rnk, n_prcs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &n_prcs);
    Msg msg = 1;
    int sum;

    if (rnk == 0) {
        broadcast(&msg, 0, rnk, n_prcs);
        sum = reduce(&msg, 0, rnk, n_prcs);
        printf("The sum is %d\n", sum);
        printf("Sending the sum to all other nodes\n");
        broadcast(&sum, 0, rnk, n_prcs);
    } else {
        broadcast(&msg, 0, rnk, n_prcs);
        reduce(&msg, 0, rnk, n_prcs);
        broadcast(&sum, 0, rnk, n_prcs);
    }

    printf("The value of sum in process %d is %d\n", rnk, sum);

    MPI_Finalize();
    return 0;
}
