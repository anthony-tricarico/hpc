#ifndef REDUCE
#define REDUCE
#include <stdio.h>
#include <mpi.h>
#include "broadcast.h"
#define GATHERING_PRC 0

Msg reduce(Msg *msg, int receiving, int rank, int n_prcs);
#endif
