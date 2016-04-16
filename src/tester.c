#include "tester.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void test_with_reruns(const char* filename, uint_fast32_t reruns) {
    struct instance inst = read_instance(filename);
    struct lagrange_solution result;
    double* times;
    
    times = malloc(reruns * sizeof(*times));
    assert(times != NULL);
    
    for(ptrdiff_t i = 0; i < reruns; i++) {
        result = solve_for_all_pw(&inst, &times[i]);
    }
    
    free_instance(&inst);
    
    print_solution(filename, &result, times, reruns);
    
    free(times);
}

void print_solution(const char* instance, const struct lagrange_solution* best, const double* times, uint_fast32_t reruns) {
    double sum = 0;
    
    for(ptrdiff_t i = 0; i < reruns; i++) {
        sum += times[i];
    }
    
    double avg = sum / (float)reruns;
    double stddev = 0;
    
    for(ptrdiff_t i = 0; i < reruns; i++) {
        stddev += powf(times[i] - avg, 2);
    }
    
    stddev = sqrtf(stddev);
    
    FILE* fd;
    
    fd = fopen("results.txt", "a");
    
    if(fd == NULL) {
        printf("Can't open results file\n");
        exit(EXIT_FAILURE);
    }
    
    int printed = fprintf(fd, "%s,%.6f,%d,%.6lf,%.6lf\n", instance, best->lagr_obj, best->capacity_violation, avg, stddev);
    
    if(printed < 0) {
        printf("Error printing results\n");
        exit(EXIT_FAILURE);
    }
    
    if(fclose(fd) != 0) {
        printf("Error closing results file\n");
        exit(EXIT_FAILURE);
    }
}