#ifndef _RELAXATION_SOLUTION_H
#define _RELAXATION_SOLUTION_H

#include <stddef.h>
#include <stdio.h>

struct relaxation_solution {
  // Total number of items in the instance
  ptrdiff_t n_items;

  // Coefficients, one per item
  float* coeff;

  // Total profit
  float profit;

  // Total used capacity
  float used_capacity;

  // Time used to find the solution
  float e_time;

  // Bound provided by the relaxation
  // (it might not coincide with the total profit,
  // e.g. in case of lagrange relaxation)
  float bound;

  // Extra param linked with the solution
  // (it can be used to store additional information,
  // e.g. the lagrange multiplier used to find the solution)
  float param;
};

// Frees the coefficient list.
void free_relaxation_solution(struct relaxation_solution* sol);

// Prints interesting info on the solution.
void print_relaxation_solution(const struct relaxation_solution* sol);

// Writes info on the soution to file fp.
void write_relaxation_solution_to_file(const struct relaxation_solution* sol, FILE* fp);

// Makes a deep copy of a solution.
struct relaxation_solution deep_copy_relaxation_solution(const struct relaxation_solution* sol);

#endif