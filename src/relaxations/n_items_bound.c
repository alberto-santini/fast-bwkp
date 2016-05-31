#include "n_items_bound.h"
#include "../sort.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

uint_fast32_t get_capacity_bound(const struct instance* inst) {
  float* w_black;
  float* w_white;
  ptrdiff_t* ids_black;
  ptrdiff_t* ids_white;

  w_black = malloc(inst->n_black * sizeof(*w_black));
  w_white = malloc(inst->n_white * sizeof(*w_white));
  ids_black = malloc(inst->n_black * sizeof(*ids_black));
  ids_white = malloc(inst->n_white * sizeof(*ids_white));

  if(w_black == NULL || w_white == NULL || ids_black == NULL || ids_white == NULL) {
    printf("Cannot allocate memory for capacity bound\n");
    exit(EXIT_FAILURE);
  }

  ptrdiff_t i_black = 0;
  ptrdiff_t i_white = 0;

  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    if(inst->colours[i] == BLACK) {
      w_black[i_black] = inst->weights[i];
      ids_black[i_black] = i_black;
      i_black++;
    } else {
      w_white[i_white] = inst->weights[i];
      ids_white[i_white] = i_white;
      i_white++;
    }
  }

  assert(i_black == inst->n_black);
  assert(i_white == inst->n_white);

  heapsort_desc(w_black, ids_black, inst->n_black);
  heapsort_desc(w_white, ids_white, inst->n_white);

  ptrdiff_t couple_id = 0;
  uint_fast32_t total_w = 0;

  while(total_w <= inst->capacity && couple_id < inst->n_black && couple_id < inst->n_white) {
    assert((int)inst->n_black - (int)couple_id >= 0);
    assert((int)inst->n_white - (int)couple_id >= 0);
    total_w += w_black[ids_black[inst->n_black - 1 - couple_id]];
    total_w += w_white[ids_white[inst->n_white - 1 - couple_id]];
    couple_id++;
  }

  free(w_black);
  free(w_white);
  free(ids_black);
  free(ids_white);

  return (total_w > inst->capacity ? couple_id - 1 : couple_id);
}