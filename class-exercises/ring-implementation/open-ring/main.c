#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_STRING 100

/* Function to read and save characters to array */
void readline(char *arr) {
    int i = 0;
    char c;
    printf("Insert message: ");
    while ((c = getchar()) != '\n') {
        arr[i++] = c;
    }
    arr[i] = '\0';
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    /* Store the total number of processes in the comunicator in
     * the variable num_processes.
     *
     * This is usually passed in as a CL argument in the mpirun
     * call*/
    int num_processes;
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);        /* The macro MPI_COMM_WORLD is very important and defines the place where all communications take place*/

    /* Store the rank of the current process, an integer going
     * from 0 to n-1 where n is the number of processes specified
     * in the CL call to mpirun after the -np flag*/
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    /* Declare an array containing characters as a buffer (this depends on the type of data that needs to be in the message) */
    char buf[MAX_STRING];
    MPI_Status status;

    /* Since the first process is the one interacting with stdin according to the MPI
     * standard, it should be here that we pass user input. */
    if (rank == 0) {
        /* Read user input with custom function */
        readline(buf);

        /* MPI_Send is the fundamental abstraction that allows one process to communicate
         * with other ones through an abstraction based on system calls that initialize 
         * sockets and other network structures that allow processes to communicate. */
        MPI_Send(buf, strlen(buf)+1, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
    } else {
        /* MPI_Recv is the second fundamental abstraction working closely with MPI_Send.
         * This function allows a sent message to be retrieved by another process thus 
         * effectively sharing data between the two processes. Interestingly, this is a 
         * synchronous call and a blocking one, meaning that if a send is not matched by a
         * receive the whole program gets stuck until the process is killed. */
        MPI_Recv(buf, MAX_STRING, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, &status);
        if (rank < num_processes - 1) {
            MPI_Send(buf, strlen(buf) + 1, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            printf("Process %d received: %s\n", rank, buf);
        }
    }

    MPI_Finalize();
    return 0;
}
