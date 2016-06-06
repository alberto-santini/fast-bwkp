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

struct relaxation_solution solve_capacity_preserving_relaxation_for_bounds(const struct instance* inst, uint_fast32_t maxb, uint_fast32_t maxw, const ptrdiff_t* ids) {
  uint_fast32_t i_black = 0;
  uint_fast32_t i_white = 0;
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

  ptrdiff_t first_skipped_black = inst->n_items;
  ptrdiff_t first_skipped_white = inst->n_items;

  while(i < inst->n_items) {
    if(i_black >= maxb && i_white >= maxw) { break; }

    if(inst->colours[ids[i]] == WHITE) {
      if(i_white < maxw) { i_white++; }
      else {
        if(first_skipped_white == inst->n_items) {
          first_skipped_white = ids[i];
        }
        i++;
        continue;
      }
    } else {
      if(i_black < maxb) { i_black++; }
      else {
        if(first_skipped_black == inst->n_items) {
          first_skipped_black = ids[i];
        }
        i++;
        continue;
      }
    }

    assert(sol.used_capacity <= inst->capacity);

    if(sol.used_capacity + inst->weights[ids[i]] <= inst->capacity) {
      sol.coeff[ids[i]] = 1.0;
      sol.used_capacity += inst->weights[ids[i]];
      sol.profit += inst->profits[ids[i]];
    } else {
      double residual_capacity = inst->capacity - sol.used_capacity;
      sol.coeff[ids[i]] = residual_capacity / (double)inst->weights[ids[i]];
      sol.used_capacity += residual_capacity;
      sol.profit += (residual_capacity * (double)inst->profits[ids[i]]) / (double)inst->weights[ids[i]];
      break;
    }

    i++;
  }

  if(sol.used_capacity < inst->capacity && i_black + i_white < inst->n_items) {
    double residual_capacity = (double)inst->capacity - (double)sol.used_capacity;

    double pw_first_skipped_white = (first_skipped_white == inst->n_items) ?
      0 : inst->pws[first_skipped_white];
    double pw_first_skipped_black = (first_skipped_black == inst->n_items) ?
      0 : inst->pws[first_skipped_black];

    ptrdiff_t expanded_item = (pw_first_skipped_black > pw_first_skipped_white) ?
      first_skipped_black : first_skipped_white;
    double expanded_item_weight = (double)inst->weights[expanded_item];
    double expanded_item_profit = (double)inst->profits[expanded_item];

    sol.coeff[expanded_item] = residual_capacity / expanded_item_weight;
    sol.profit += residual_capacity * expanded_item_profit / expanded_item_weight;
    sol.used_capacity = inst->capacity;
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

  uint_fast32_t maxb = (inst->n_black < inst->n_white ? inst->n_black : inst->n_white + 1);
  uint_fast32_t maxw = (inst->n_black < inst->n_white ? inst->n_black + 1 : inst->n_white);

  struct timespec start, end;

  get_monotonic_time(&start);
  uint_fast32_t cap_bound = get_capacity_bound(inst);
  get_monotonic_time(&end);

  double bound_time = get_elapsed_time_ms(&start, &end);
  struct relaxation_solution sol;

  if(cap_bound < maxb && cap_bound < maxw) {
    struct relaxation_solution sol1, sol2;

    sol1 = solve_capacity_preserving_relaxation_for_bounds(inst, cap_bound, cap_bound + 1, ids);
    sol2 = solve_capacity_preserving_relaxation_for_bounds(inst, cap_bound + 1, cap_bound, ids);

    if(sol1.profit > sol2.profit) {
      sol = sol1;
      sol.e_time += sol2.e_time;
      sol.param = cap_bound;
    } else {
      sol = sol2;
      sol.e_time += sol1.e_time;
      sol.param = cap_bound;
    }
  } else {
    sol = solve_capacity_preserving_relaxation_for_bounds(inst, maxb, maxw, ids);
    sol.param = (maxb < maxw ? maxb : maxw);
  }

  sol.e_time += bound_time;

  free(ids);
  return sol;
}