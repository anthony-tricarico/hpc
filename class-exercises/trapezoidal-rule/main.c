/* We can use the trapezoidal rule to to approximate the area between the graph of a
 * function, y = f(x), two vertical lines, and the x-axis */
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define GATHERING_PROCESS 0

/* let's take f to be a simple quadratic function */
float f(float x) {
    return (-1 * pow(x, 2)) + (3 * x) + 5;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rnk, n_prcs;
    float msg, res, h, b, a, x_i, y_i;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rnk);
    MPI_Comm_size(MPI_COMM_WORLD, &n_prcs);

    /* I want the gathering process to receive all the necessary operands 
     * to then perform the addition and return the result. 
     * Although there are no guarantees as to which process will send first
     * the result we can control the flow using blocking receive calls in
     * the gathering process. In this case this could also be handled async
     * since the order of operands does not matter in addition (commutative)
     * but it is still nice that it is possible to ensure a specific ordering if needed. */
    if (rnk == GATHERING_PROCESS) {
        printf("Enter value for a: ");
        scanf("%f", &a);
        printf("Enter value for b: ");
        scanf("%f", &b);

        h = (b-a)/(float)n_prcs;
        // printf("h is now: %.2f\n", h);
        float res = (f(a) + f(b)) / 2.0;
        for (int i = GATHERING_PROCESS+1; i < n_prcs; i++) {
            MPI_Send(&a, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&h, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
        }
        for (int i = GATHERING_PROCESS+1; i < n_prcs; i++) {
            MPI_Recv(&y_i, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &status);
            // printf("value received is %.2f\n", y_i);
            res += y_i;
            // printf("res is now: %.2f\n", res);
        }
        // printf("h is now: %.2f\n", h);
        res = h*res;
        // printf("res is now: %.2f\n", res);
        printf("The area under the function between %.2f and %.2f is: %.2f\n", a, b, res);
    } else {
        MPI_Recv(&a, 1, MPI_FLOAT, GATHERING_PROCESS, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, 1, MPI_FLOAT, GATHERING_PROCESS, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&h, 1, MPI_FLOAT, GATHERING_PROCESS, 0, MPI_COMM_WORLD, &status);

        x_i = a + rnk * h;
        y_i = f(x_i);
        MPI_Send(&y_i, 1, MPI_FLOAT, GATHERING_PROCESS, 0, MPI_COMM_WORLD); 

    }

    MPI_Finalize();
    return 0;
}

