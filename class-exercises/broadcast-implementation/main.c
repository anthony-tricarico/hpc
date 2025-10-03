#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define MAX_LEN 100

int main(int argc, char **argv) {
    /* Initialize MPI environment */
    MPI_Init(&argc, &argv);

    /* Declare pointer to struct *Status */
    MPI_Status status;
    MPI_Request request;

    int rnk, num_prcs;
    char msg[MAX_LEN];

    /* Get rank of current process */
    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    
    /* Get number of all processses from mpirun CL call*/
    MPI_Comm_size(MPI_COMM_WORLD, &num_prcs);

    /* Goal: a process p wants to share the content of a variable "a" with
     * all the other processes. 
     * This means that process p should be sending while all other processes
     * should be receiving. */
        
    /* Below is the simplest implementation of a broadcast where process 0 is always 
     * the one passing information to all other processes. 
     *
     * The asymptotic time complexity is O(n) since process 0 needs to send 
     * a message to all other (n-1) processes. */
    #ifdef ZERO_PROCESS
    const int p = 0;      /* process p set to process 0 */

    if (rnk == p) {
        printf("Enter message: ");
        scanf("%s", msg);
        for (int i = p+1; i < num_prcs; i++)
            MPI_Send(msg, strlen(msg)+1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(msg, MAX_LEN, MPI_CHAR, p, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received: %s\n", rnk, msg);
    }
    #endif

    /* TODO: Implement other algorithms that have better scalability */

    return 0;
}
