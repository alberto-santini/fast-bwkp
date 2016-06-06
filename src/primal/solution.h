#ifndef _PRIMAL_SOLUTION_H
#define _PRIMAL_SOLUTION_H

#include <stddef.h>
#include <stdio.h>

struct primal_solution {
  // Total number of items in the instance
  ptrdiff_t n_items;

  // Coefficients, one per item
  double* coeff;

  // Total profit
  double profit;

  // Total used capacity
  double used_capacity;

  // Time used to find the solution
  double e_time;
  
  // Optimality gap (if known)
  double gap;
};

// Frees the coefficient list.
void free_primal_solution(struct primal_solution* sol);

// Prints interesting info on the solution.
void print_primal_solution(const struct primal_solution* sol);

// Writes info on the soution to file fp.
void write_primal_solution_to_file(const struct primal_solution* sol, FILE* fp);

#endif