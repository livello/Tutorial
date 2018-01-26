#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_statistics.h>

#define MAX_STATES_INITIAL 100000
#define MAX_GATE_SHIFT 7000
struct gate_state {
    long time;
    int gate_position;
};


int compare_int (const void *, const void *);
int main(int argc, char *args[]) {
    int size_states = MAX_STATES_INITIAL;
    char* filename;
    long *time_states = malloc(size_states * sizeof(*time_states));
    int *shift_states = malloc(size_states * sizeof(*shift_states));
    int fd;
    if (argc < 2) {
        filename="/home/irinaart/Documents/GateStates.txt_log.txt";
    }
    else
        filename = args[1];
    int lines_saved_done = 0;
    long total_gate_shift = 0, time_delta = 0;
    struct gate_state state_current, state_last;
    state_last.gate_position = 0;
    state_last.time = 0L;

    fprintf(stdout, "Opening file: %s", filename);
    FILE *file_input;
    char *current_line = NULL;
    char *string_buffer = NULL;
    size_t length_read = 0;
    file_input = fopen(filename, "r");
    if (file_input == NULL)
        exit(1);

    while (getline(&current_line, &length_read, file_input) != -1) {
        if (strlen(current_line) < 50)
            continue;
//        printf("%s", current_line);
        string_buffer = (char *) malloc(14);
        strncpy(string_buffer, current_line, 13);
        state_current.time = atol(string_buffer);
        strncpy(string_buffer, current_line + 39, 11);
        state_current.gate_position = atoi(string_buffer);
        time_delta = (state_current.time - state_last.time);
        int shift_position = abs(state_current.gate_position - state_last.gate_position);
        if (shift_position > MAX_GATE_SHIFT) {
            printf("Shift too big: %i  Total gate shift: %ld STRING:     %s", shift_position, total_gate_shift,
                   current_line);
        } else if(shift_position>0){
            total_gate_shift += shift_position;
            lines_saved_done++;
        }

        state_last.time = state_current.time;
        state_last.gate_position = state_current.gate_position;
        if (lines_saved_done > size_states - 3) {
            size_states = size_states + MAX_STATES_INITIAL;
            time_states = (long *)realloc(time_states, size_states*sizeof(long));
            shift_states = (int *)realloc(shift_states, size_states*sizeof(int));

        }

//                printf("lines_saved_done: %i \n",lines_saved_done);
                time_states[lines_saved_done]=state_current.time;
                shift_states[lines_saved_done]=shift_position;
    }

    free(current_line);
    free(string_buffer);
    fclose(file_input);
    printf("\n \n Total shifting is: %ld \n", total_gate_shift);


    double mean, variance, largest, smallest;

//    mean     = gsl_stats_mean(shift_states, 1, lines_saved_done-1);
//    variance = gsl_stats_variance(shift_states, 1, lines_saved_done-1);
//    largest  = gsl_stats_max(shift_states, 1, lines_saved_done-1);
//    smallest = gsl_stats_min(shift_states, 1, lines_saved_done-1);
//
//    printf ("The sample mean is %g\n", mean);
//    printf ("The estimated variance is %g\n", variance);
//    printf ("The largest value is %g\n", largest);
//    printf ("The smallest value is %g\n", smallest);
    qsort(shift_states,lines_saved_done,sizeof(int),compare_int);
    for(int i=lines_saved_done-2;i>lines_saved_done-1000;i--)
        printf(":%i",shift_states[i]);
//printf()
    return 0;
}
int compare_int (const void *a, const void *b)
{
    const int *da = (const int *) a;
    const int *db = (const int *) b;

    return (*da > *db) - (*da < *db);
}

