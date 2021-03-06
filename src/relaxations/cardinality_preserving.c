#include "cardinality_preserving.h"
#include "n_items_bound.h"
#include "../sort.h"
#include "../timing.h"
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct relaxation_solution solve_cardinality_preserving_relaxation_for_bounds(const struct instance* inst, uint_fast64_t maxb, uint_fast64_t maxw, const ptrdiff_t* ids) {
  uint_fast64_t i_black = 0;
  uint_fast64_t i_white = 0;
  uint_fast64_t i = 0;

  struct timespec start, end;
  struct relaxation_solution sol = { .n_items = inst->n_items, .profit = 0, .used_capacity = 0, .bound = 0, .param = 0 };

  sol.coeff = malloc(inst->n_items * sizeof(*(sol.coeff)));
  if(sol.coeff == NULL) {
    printf("Cannot allocate memory for solution coeffs\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < inst->n_items; i++) { sol.coeff[i] = 0.0; }

  get_monotonic_time(&start);
  while(i < inst->n_items) {
    if(i_black >= maxb && i_white >= maxw) { break; }

    if(inst->colours[ids[i]] == WHITE) {
      if(i_white < maxw) { i_white++; }
      else { i++; continue; }
    } else {
      if(i_black < maxb) { i_black++; }
      else { i++; continue; }
    }

    sol.coeff[ids[i]] = 1.0;
    sol.used_capacity += inst->weights[ids[i]];
    sol.profit += inst->profits[ids[i]];

    i++;
  }
  get_monotonic_time(&end);

  sol.bound = sol.profit;
  sol.param = maxb;
  sol.e_time = get_elapsed_time_ms(&start, &end);

  return sol;
}

struct relaxation_solution solve_cardinality_preserving_relaxation(const struct instance* inst) {
  ptrdiff_t* ids;
  double* profits;

  ids = malloc(inst->n_items * sizeof(*ids));
  if(ids == NULL) {
    printf("Cannot allocate memory for ids\n");
    exit(EXIT_FAILURE);
  }

  profits = malloc(inst->n_items * sizeof(*ids));
  if(profits == NULL) {
    printf("Cannot allocate memory for dbl profits\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    ids[i] = i;
    profits[i] = (double)inst->profits[i];
  }
  heapsort_desc(profits, ids, inst->n_items);

  struct timespec start, end;

  get_monotonic_time(&start);
  struct n_items_bound cap_bound = get_capacity_bound(inst);
  get_monotonic_time(&end);

  double bound_time = get_elapsed_time_ms(&start, &end);
  struct relaxation_solution sol;

  if(cap_bound.type == BOUND_FIXED) {
    sol = solve_cardinality_preserving_relaxation_for_bounds(inst, cap_bound.black, cap_bound.white, ids);
  } else {
    assert(cap_bound.type == BOUND_ANY);
    
    struct relaxation_solution sol1, sol2;

    sol1 = solve_cardinality_preserving_relaxation_for_bounds(inst, cap_bound.black, cap_bound.white + 1, ids);
    sol2 = solve_cardinality_preserving_relaxation_for_bounds(inst, cap_bound.black + 1, cap_bound.white, ids);

    if(sol1.profit > sol2.profit) {
      sol = sol1;
      sol.e_time += sol2.e_time;
    } else {
      sol = sol2;
      sol.e_time += sol1.e_time;
    }
  }
  
  sol.e_time += bound_time;

  free(ids);
  free(profits);
  return sol;
}