#include "capacity_preserving.h"
#include "n_items_bound.h"
#include "../sort.h"
#include "../timing.h"
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct relaxation_solution solve_capacity_preserving_relaxation_for_bound(const struct instance* inst, uint_fast32_t maxi, const ptrdiff_t* ids) {
  uint_fast32_t i = 0;

  struct timespec start, end;
  struct relaxation_solution sol = { .n_items = inst->n_items, .profit = 0, .used_capacity = 0, .bound = 0, .param = 0 };

  sol.coeff = malloc(inst->n_items * sizeof(*(sol.coeff)));
  if(sol.coeff == NULL) {
    printf("Cannot allocate memory for solution coeffs\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < inst->n_items; i++) { sol.coeff[i] = 0.0; }
  
  get_monotonic_time(&start);

  while(i < maxi) {
    if(sol.used_capacity + inst->weights[ids[i]] <= inst->capacity) {
      sol.coeff[ids[i]] = 1.0;
      sol.used_capacity += inst->weights[ids[i]];
      sol.profit += inst->profits[ids[i]];
    } else {      
      double residual_capacity = (double)inst->capacity - (double)sol.used_capacity;
      
      sol.coeff[ids[i]] = residual_capacity / (double)inst->weights[ids[i]];
      sol.used_capacity = inst->capacity;
      sol.profit += residual_capacity * (double)inst->profits[ids[i]] / (double)inst->weights[ids[i]];

      break;
    }

    i++;
  }

  if(sol.used_capacity < inst->capacity && i < inst->n_items) {    
    double residual_capacity = (double)inst->capacity - (double)sol.used_capacity;

    sol.coeff[ids[i]] = residual_capacity / (double)inst->weights[ids[i]];
    sol.used_capacity = inst->capacity;
    sol.profit += residual_capacity * (double)inst->profits[ids[i]] / (double)inst->weights[ids[i]];
  }

  get_monotonic_time(&end);
  sol.bound = sol.profit;
  sol.e_time = get_elapsed_time_ms(&start, &end);

  return sol;
}

struct relaxation_solution solve_capacity_preserving_relaxation(const struct instance* inst) {
  ptrdiff_t* ids;

  ids = malloc(inst->n_items * sizeof(*ids));
  if(ids == NULL) {
    printf("Cannot allocate memory for ids\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < inst->n_items; i++) { ids[i] = i; }
  heapsort_desc(inst->pws, ids, inst->n_items);

  struct timespec start, end;

  get_monotonic_time(&start);
  uint_fast32_t cap_bound = get_capacity_bound(inst);
  get_monotonic_time(&end);
  
  // If we can pack n white and n black items,
  // but we can't pack n+1 white and n+1 black items,
  // we can say that we can pack at most 2*n+1 items:
  cap_bound *= 2;
  cap_bound += 1;
  
  assert(cap_bound <= inst->n_items);

  double bound_time = get_elapsed_time_ms(&start, &end);
  struct relaxation_solution sol;
  
  sol = solve_capacity_preserving_relaxation_for_bound(inst, cap_bound, ids);
  
  sol.param = cap_bound;
  sol.e_time += bound_time;

  free(ids);
  return sol;
}