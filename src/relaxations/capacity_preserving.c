#include "capacity_preserving.h"
#include "../sort.h"
#include "../timing.h"
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

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
  struct relaxation_solution sol = {.n_items = inst->n_items, .profit = 0, .used_capacity = 0, .param = 0};
  
  sol.coeff = malloc(inst->n_items * sizeof(*(sol.coeff)));
  if(sol.coeff == NULL) {
    printf("Cannot allocate memory for solution coeffs\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < inst->n_items; i++) { sol.coeff[i] = 0.0; }
  
  ptrdiff_t packed_items = 0;
  
  get_monotonic_time(&start);
  while(packed_items < inst->n_items && sol.used_capacity < inst->capacity) {
    if(sol.used_capacity + inst->weights[ids[packed_items]] <= inst->capacity) {
      sol.profit += (double)inst->profits[ids[packed_items]];
      sol.used_capacity += (double)inst->weights[ids[packed_items]];
      sol.coeff[ids[packed_items]] = 1.0;
    } else {
      double residual_capacity = (double)inst->capacity - sol.used_capacity;
      double element_weight = (double)inst->weights[ids[packed_items]];
      double element_ratio = residual_capacity / element_weight;
      sol.profit += element_ratio * (double)inst->profits[ids[packed_items]];
      sol.used_capacity = (double)inst->capacity;
      sol.coeff[ids[packed_items]] = element_ratio;
      break;
    }
    packed_items++;
  }
  get_monotonic_time(&end);
  
  sol.bound = sol.profit;
  sol.e_time = get_elapsed_time_ms(&start, &end);

  free(ids);
  return sol;
}