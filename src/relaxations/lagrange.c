#include "lagrange.h"
#include "../sort.h"
#include "../timing.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct relaxation_solution solve_lagrange_relaxation(const struct instance* inst) {
  ptrdiff_t n_unique_pws = 0;
  float* unique_pws = unique_desc(inst->pws, inst->n_items, &n_unique_pws);

  struct relaxation_solution sol = solve_lagrange_for_multiplier(inst, 0.0);
  float total_time = sol.e_time;

  if(sol.used_capacity <= inst->capacity) { return sol; }

  struct relaxation_solution best = sol;

  for(ptrdiff_t l = 0; l < n_unique_pws; l++) {
    sol = solve_lagrange_for_multiplier(inst, unique_pws[n_unique_pws - 1 - l]);

    total_time += sol.e_time;
    if(sol.bound < best.bound) { best = deep_copy_relaxation_solution(&sol); }
    
    if(sol.used_capacity <= inst->capacity) { break; }
  }

  free(unique_pws);
  free_relaxation_solution(&sol);

  best.e_time = total_time;
  return best;
}

#define LPB(i) lagr_p_black[ids_black[i]]
#define LPW(i) lagr_p_white[ids_white[i]]
#define PB(i) p_black[ids_black[i]]
#define PW(i) p_white[ids_white[i]]
#define WB(i) w_black[ids_black[i]]
#define WW(i) w_white[ids_white[i]]
#define OB(i) orig_id_black[ids_black[i]]
#define OW(i) orig_id_white[ids_white[i]]

struct relaxation_solution solve_lagrange_for_multiplier(const struct instance* inst, float multiplier) {
  float* lagr_p_black;
  float* lagr_p_white;
  uint_fast32_t* w_black;
  uint_fast32_t* w_white;
  uint_fast32_t* p_black;
  uint_fast32_t* p_white;
  ptrdiff_t* orig_id_black;
  ptrdiff_t* orig_id_white;

  lagr_p_black = malloc(inst->n_black * sizeof(*lagr_p_black));
  lagr_p_white = malloc(inst->n_white * sizeof(*lagr_p_white));
  p_black = malloc(inst->n_black * sizeof(*p_black));
  p_white = malloc(inst->n_white * sizeof(*p_white));
  w_black = malloc(inst->n_black * sizeof(*w_black));
  w_white = malloc(inst->n_white * sizeof(*w_white));
  orig_id_black = malloc(inst->n_black * sizeof(orig_id_black));
  orig_id_white = malloc(inst->n_white * sizeof(orig_id_white));

  if(lagr_p_black == NULL || lagr_p_white == NULL || w_black == NULL || w_white == NULL || p_black == NULL || p_white == NULL || orig_id_black == NULL || orig_id_white == NULL) {
    printf("Cannot allocate memory for lagrange vectors\n");
    exit(EXIT_FAILURE);
  }

  struct timespec start, end;
  get_monotonic_time(&start);

  ptrdiff_t i_black = 0, i_white = 0;

  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    float lagr_profit = inst->profits[i] - multiplier * inst->weights[i];

    if(inst->colours[i] == BLACK) {
      lagr_p_black[i_black] = lagr_profit;
      p_black[i_black] = inst->profits[i];
      w_black[i_black] = inst->weights[i];
      orig_id_black[i_black] = i;
      i_black++;
    } else {
      lagr_p_white[i_white] = lagr_profit;
      p_white[i_white] = inst->profits[i];
      w_white[i_white] = inst->weights[i];
      orig_id_white[i_white] = i;
      i_white++;
    }
  }

  assert(i_black == inst->n_black);
  assert(i_white == inst->n_white);

  ptrdiff_t* ids_black;
  ptrdiff_t* ids_white;

  ids_black = malloc(inst->n_black * sizeof(*ids_black));
  ids_white = malloc(inst->n_white * sizeof(*ids_white));

  if(ids_black == NULL || ids_white == NULL) {
    printf("Cannot allocate memory for lagrange id vectors\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < inst->n_black; i++) { ids_black[i] = i; }
  for(ptrdiff_t i = 0; i < inst->n_white; i++) { ids_white[i] = i; }

  heapsort_desc(lagr_p_black, ids_black, inst->n_black);
  heapsort_desc(lagr_p_white, ids_white, inst->n_white);

  i_black = 0;
  i_white = 0;

  struct relaxation_solution sol = { .n_items = inst->n_items, .used_capacity = 0, .profit = 0, .bound = multiplier * (float)inst->capacity, .param = multiplier };

  sol.coeff = malloc(inst->n_items * sizeof(*(sol.coeff)));
  if(sol.coeff == NULL) {
    printf("Cannot allocate memory for solution coefficients\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < inst->n_items; i++) { sol.coeff[i] = 0.0; }

  while(i_black < inst->n_black && i_white < inst->n_white) {
    if(LPB(i_black) + LPW(i_white) >= 0) {
      sol.bound += LPB(i_black) + LPW(i_white);
      sol.used_capacity += WB(i_black) + WW(i_white);
      sol.profit += PB(i_black) + PW(i_white);
      sol.coeff[OB(i_black)] = 1.0;
      sol.coeff[OW(i_white)] = 1.0;
    } else {
      if(LPB(i_black) >= 0) {
        sol.bound += LPB(i_black);
        sol.used_capacity += WB(i_black);
        sol.profit += PB(i_black);
        sol.coeff[OB(i_black)] = 1.0;
      }
      if(LPW(i_white) >= 0) {
        sol.bound += LPW(i_white);
        sol.used_capacity += WW(i_white);
        sol.profit += PW(i_white);
        sol.coeff[OW(i_white)] = 1.0;
      }
      break;
    }

    i_black++;
    i_white++;

    if(i_white == inst->n_white && i_black < inst->n_black) {
      if(LPB(i_black) >= 0) {
        sol.bound += LPB(i_black);
        sol.used_capacity += WB(i_black);
        sol.profit += PB(i_black);
        sol.coeff[OB(i_black)] = 1.0;
      }
      break;
    }

    if(i_black == inst->n_black && i_white < inst->n_white) {
      if(LPW(i_white) >= 0) {
        sol.bound += LPW(i_white);
        sol.used_capacity += WW(i_white);
        sol.profit += PW(i_white);
        sol.coeff[OW(i_white)] = 1.0;
      }
      break;
    }
  }

  get_monotonic_time(&end);
  sol.e_time = get_elapsed_time_ms(&start, &end);

  free(lagr_p_black);
  free(lagr_p_white);
  free(p_black);
  free(p_white);
  free(w_black);
  free(w_white);
  free(orig_id_black);
  free(orig_id_white);
  free(ids_black);
  free(ids_white);

  return sol;
}