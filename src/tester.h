#ifndef _TESTER_H
#define _TESTER_H

#include "instance.h"
#include "lagrange.h"

// Runs the algorithm ``reruns'' times.
void test_with_reruns(const char* filename, uint_fast32_t reruns);

// Appends the results to ``results.txt''.
void print_solution(const char* instance, const struct lagrange_solution* best, const double* times, uint_fast32_t reruns);

#endif