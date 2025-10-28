#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* returns a pointer to the struct containing the current seconds and microseconds (when the function is called) */
struct timeval *get_time_struct(void) {
    struct timeval *time = malloc(sizeof(struct timeval));
    struct timezone *tz = malloc(sizeof(struct timezone));
    // error handling
    short time_flg = gettimeofday(time, tz);
    if (time_flg != 0) {
        fprintf(stderr, "Error when calling function gettime. Exiting program execution.\n");
        exit(EXIT_FAILURE);
    }

    return time;
    
}

#ifdef TEST
int main(void) {
    struct timeval *time = get_time_struct();
    // printf("Number of seconds: %ld\n", time->tv_sec);
    // printf("Number of microseconds: %d\n", time->tv_usec);

    struct timeval *time_end = get_time_struct();
    printf("Program execution took: %ld seconds\t%d microseconds\n", time_end->tv_sec - time->tv_sec, time_end->tv_usec - time->tv_usec);

    return 0;
}
#endif
