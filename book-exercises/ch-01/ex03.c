/* Try to write pseudo-code for the tree-structured global sum illustrated in Figure 1.1. Assume
 * the number of cores is a power of two (1, 2, 4, 8, ...)*/

/* pseudo-code 
 * int divisor = 2, core_difference = 1
 * enum flag {sending, receiving};
 * while (divisor less than last core number) do
 *      if (core number % divisor == 0)
 *          core receives
 *          core adds
 *      else
 *          core sends
 *
 *      if (core number + core_difference == other_core number)
 *          pair core number and other_core number
 *      divisor *= 2
 *      core_difference *= 2
 *      */
