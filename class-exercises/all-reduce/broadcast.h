/* Header for broadcast-related functions */
#ifndef BROADCAST
#define BROADCAST
#include <stdio.h>
#include <mpi.h>
typedef int Msg;
MPI_Status status;
void broadcast(Msg *msg, int sending, int rank, int n_prcs);
#endif
