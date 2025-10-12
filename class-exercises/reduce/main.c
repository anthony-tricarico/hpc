#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define GATHERING_PRC 0

typedef int Item;
typedef enum {
    ADD, 
    MAX, 
    MIN
} Operation;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rnk, n_prcs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &n_prcs);

    MPI_Status status;
    Item msg;

    if (rnk == GATHERING_PRC) {
        #ifdef ACCEPT_IN
        /* Request input and initialize message */
        printf("Initialize integer variable, input a value: ");
        scanf("%d", &msg);
        #endif
        // declare op variable to contain operation
        Operation op;
        char *input;
                
        // assign the correct value to op based on user input
        // strcmp evaluates to 0 when two strings passed in as
        // arguments are the same in terms of the chars they contain. 
        bool flg_check = true;     // check flag to see if the user input for op
                                   // is correct
        while (flg_check) {
            printf("Declare type of operation you want to perform (ADD, MAX, MIN): ");
            scanf("%s", input);
            if (strcmp(input, "ADD") == 0) {
                op = ADD;
                flg_check = false;
            } else if (strcmp(input, "MAX") == 0) {
                op = MAX;
                flg_check = false;
            } else if (strcmp(input, "MIN") == 0) {
                op = MIN;
                flg_check = false;
            } else {
                printf("The operation is not recognized.\nUse one of ADD, MAX, MIN\n");
            }
        }

        #ifdef ACCEPT_IN
        /* Send messages to the following node */
        MPI_Send(&msg, 1, MPI_INT, rnk + 1, 0, MPI_COMM_WORLD);
        #endif
        int res;
        /* Iterate over all other processes to retrieve data from those */
        if (op == ADD) {
            res = 0;
            for (int i = GATHERING_PRC + 1; i < n_prcs; i++) {
                MPI_Recv(&msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                res += msg;
            }
        } else if (op == MAX) {
            res = INT_MIN;
             for (int i = GATHERING_PRC + 1; i < n_prcs; i++) {
                MPI_Recv(&msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                if (msg > res) 
                    res = msg;
            }
        } else if (op == MIN) {
                res = INT_MAX;
                for (int i = GATHERING_PRC + 1; i < n_prcs; i++) {
                MPI_Recv(&msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                if (msg < res) 
                    res = msg;
            }
        }
        printf("The final value is %d\n", res);
    } else {
        // branch for execution when input is passed by the user.
        #ifdef ACCEPT_IN
        /* Receive message from previous rank */
        MPI_Recv(&msg, 1, MPI_INT, rnk - 1, 0, MPI_COMM_WORLD, &status);
        /* Increase msg by one */
        msg++;
        #endif

        // branch for execution when no input is passed by the user
        // initialization of message happens in process with rnk 1 and
        // is then passed to all the other processes until the last one
        // is reached.
        #ifdef NO_IN
        /* Receive message from previous rank */
        if (rnk > 1) {
            MPI_Recv(&msg, 1, MPI_INT, rnk - 1, 0, MPI_COMM_WORLD, &status);
            /* Increase msg by one */
            msg++;
        }
        #endif

        /* Checks that the process is not the last one and if it is not it sends to the next process */
        if (rnk == 1) msg = 2;
        if (rnk != n_prcs - 1) 
            MPI_Send(&msg, 1, MPI_INT, rnk + 1, 0, MPI_COMM_WORLD);
        /* Anyway all the data must go to the GATHERING_PRC to be operated on */
        MPI_Send(&msg, 1, MPI_INT, GATHERING_PRC, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
