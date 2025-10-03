#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    int rank, size;
    int data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Root (id=0) initializes the message
    if (rank == 0) {
        data = 6;
        printf("Process %d is root, broadcasting value %d\n", rank, data);
    } else {
        // All others must first receive from their parent
        MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Broadcast according to binary tree algorithm
    int maxLevel = (int)ceil(log2(size));
    for (int i = maxLevel - 1; i >= 0; i--) {
        int step = 1 << i;  // 2^i
        if (rank % (step * 2) == 0 && rank + step < size) {
            MPI_Send(&data, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD);
        }
    }

    printf("Process %d received data = %d from process\n", rank, data);

    MPI_Finalize();
    return 0;
}
