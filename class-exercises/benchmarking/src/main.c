#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "get_time.h"

#define MAX_LIM 30
#define BYTES_TO_MBS(x) (x * 1000000)

int main(void) {
    MPI_Init(NULL, NULL);
    int rnk, n_prcs;

    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &n_prcs);
    MPI_Status status;

    if (rnk == 0) {
        unsigned long int n = 1;
        double mbs = 0.0;
        long unsigned size ;
        printf("kind\t\tn\t\ttime (sec)\t\tRate (MB/sec)\n");
        while (n <= (1L<<MAX_LIM)) {
            // collect time at beginning of each iteration
            struct timeval *time = get_time_struct();
            // variable to store time elapsed
            double time_elapsed;
            // allocate memory based on how many bytes need to be sent
            size = sizeof(char) * n;
            // printf("size is %lu\n", size);
            char *buf = malloc(size);

            // printf("buffer successfully allocated\n");
            // populate the buffer with 1s
            for (long unsigned i = 0; i < n; i++)
                buf[i] = '1';
            // printf("buffer successfully populated\n");
            // send message about size to other process
            MPI_Send(&size, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD);

            // send message with array to other process
            MPI_Send(buf, n, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

            // receive message
            MPI_Recv(buf, n, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
            // printf("LOG: received back values for array\n");
            // print_arr(buf, size);
            
            // record time it took and log it
            struct timeval *time_end = get_time_struct();
            // record time elapsed in seconds
            time_elapsed = (time_end->tv_sec - time->tv_sec) + ((time_end->tv_usec - time->tv_usec) / 1000000.0);
            // compute MBs per second
            mbs = n / (time_elapsed * 1e6);
            // print everything nicely formatted
            // printf("send/receive\t\t%d\t\t%.6f\t\t%.6f\n", n, time_elapsed, mbs);
            printf("%-14s%15lu%20.6f%20.6f\n", "send/receive", n, time_elapsed, mbs);
            // deallocate memory at the end of each iteration
            free(buf);
            n = (n << 1);
        }
    } else {
        long unsigned size;
        unsigned long int n = 1;
        while (n <= (1L<<MAX_LIM)) {
            // receive size of buffer and save it
            MPI_Recv(&size, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD, &status);

            // initialize buffer with size
            char *buf = malloc(size);

            // receive message about buffer and store it
            MPI_Recv(buf, n, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

            // send back the message
            MPI_Send(buf, n, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

            free(buf);
            n = (n << 1);
        }
    }

    MPI_Finalize();
    return 0;
}
