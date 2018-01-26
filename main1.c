#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES_INITIAL 10
struct gate_state {
    long time;
    int gate_position;
};


int main() {
    int size_states = MAX_STATES_INITIAL;
    long *time_states = (long *)malloc(size_states * sizeof(*time_states));
    int *shift_states = (int * )malloc(size_states * sizeof(*shift_states));
    int i=0;
    for (;i<100;i++){
    printf("Proceed element %i ",i);
        (time_states)[i]=2000000;
        printf("time_states= %ld \n",time_states[i]);
//        *(shift_states+i)=10*i;
        if (i > size_states - 3) {
            printf("Realloc time_states[%i]:%ld \n",i,time_states[i]);
            size_states = size_states + MAX_STATES_INITIAL;
            time_states = (long *)realloc(time_states, size_states*sizeof(long));
//            shift_states = (int *)realloc(shift_states, size_states);

        }
    }
    printf("Total lines_count: %i \n",i);
    return 0;
}

