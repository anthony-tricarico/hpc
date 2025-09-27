/* Devise formulas for the functions that calculate my_first_i and my_last_i in the global
 * sum example. Remember that each core should be assigned roughly the same number of elements of
 * computations in the loop.*/

/* First determine the number of cores we will be using. Let's assume for simplicity that we have 12
 * cores to work with in this example. Now each core will need to have approximately n / 12 operations
 * to perform. These can in turn be assigned using a load balancing algorithm. However, assuming that n
 * is a multiple of 12 we can make sure that each core will have a even number of operations to perform
 * and those will be distributed equally across cores.
 *
 * Now, we have to determine how cores will communicate and which parallel programming paradigm we are
 * using. In case of a shared memory setting, it would be easy for any other core to access the value
 * stored by another core. This would imply that if I am initializing my instructions across cores
 * starting from core 0 up to core 11 then my_first_i will be 0, my_last_i will be n / 12 but now
 * core 1 can read the value of n / 12 and add an offset of 1 to get the next value to perform a
 * partial sum. This process will go on for all the other cores until all cores have an instance of
 * the two variables.
 *
 * Another formula that could be used knowing that the load balancer will try to assign an homogeneous
 * number of operations to each core is simple and does not rely on a shared memory paradigm.
 * In this case, we could work with offsets so that every time each core will have the variables
 * initialized as follows:
 * my_first_i = core_num * n/12
 * my_last_i = my_first_i + n/12 
 *
 * where core_num indicates the number of the core starting from 0. This way the first core (0) has
 * the following two values assigned to them:
 * my_first_i = 0 * n/12 = 0
 * my_last_i = my_first_i + n/12
 *
 * Notice that in the current implementation it is not an issue if my_last_i in core 0 overlaps with
 * my_first_i in core 1 since the sum loop is written as:
 *
 * for (int my_i = my_first_i; my_i < my_last_i; my_i++)
 *      my_sum += x[my_i];
 *
 * my_i is never equal to my_last_i*/
