#include <stdio.h>
#include <stdlib.h>
#define MAX_CORES 8
#define TRUE 1
#define FALSE 0
#define REMOVED 12345

typedef int Core_num;

struct pairs {
    int arr[2];
    struct pairs *next;
};

struct pairs *init_pairs(void) {
    struct pairs *p;
    return p;
}

void remove_match(int *arr, int num) {
    for (int i = 0; i < MAX_CORES; i++) {
        if (arr[i] == num)
            arr[i] = REMOVED;
    }
}

void print_arr(int *arr) {
    for (int i = 0; i < MAX_CORES; i++) {
        if (arr[i] != REMOVED)  printf("%d ", arr[i]);
        else                    printf("removed ");
    }
    printf("\n");
}

int find_match(int *arr) {
    int bitmask = 0b001;
    int res;
    int stage = 1;
    bitmask = bitmask << (stage - 1);
    // go over the list of cores and find the correct one
    for (int i = 0; i < MAX_CORES; i++) {
        if (arr[i] != REMOVED) {
            res = arr[i] ^ bitmask;
            struct pairs *c = init_pairs();
            struct pairs *p = init_pairs();
            p->arr[0] = arr[i];
            p->arr[1] = res;
            p->next = c;
            remove_match(arr, res);
        } else {
            ;
        }
    }
}

int main(void) {
    /*
    int first_stage = 0b001;
    int second_stage = 0b010;
    int third_stage = 0b100;
    */

    /* Initialize array of core numbers */

    int core_nums[MAX_CORES];
    for (int i = 0; i < MAX_CORES; i++)
        core_nums[i] = i;

    // first stage: pair with cores whose number in binary differs only in the rightmost bit
    // this example shows why core 0 would end up paired with core 1
    printf("first stage 0 gets paired with: %d\n", find_match(core_nums));        
    printf("first stage 0 gets paired with: %d\n", find_match(core_nums));        
    printf("first stage 0 gets paired with: %d\n", find_match(core_nums));        
    print_arr(core_nums);


#if 0
    printf("second stage 0 gets paired with: %d\n", find_match(0, 2));        
    printf("third stage 0 gets paired with: %d\n", find_match(0, 3));

    printf("first stage 1 gets paired with: %d\n", find_match(1, 1));        
    printf("second stage 1 gets paired with: %d\n", find_match(1, 2));        
    printf("third stage 1 gets paired with: %d\n", find_match(1, 3));        
#endif

    return 0;
}
