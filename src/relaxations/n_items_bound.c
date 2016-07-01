#include "n_items_bound.h"
#include "../sort.h"

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

struct n_items_bound get_capacity_bound(const struct instance* inst) {
  double* w_black;
  double* w_white;
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
  uint_fast64_t total_w = 0;
  
  #define FREE_ALL \
    free(w_black); \
    free(w_white); \
    free(ids_black); \
    free(ids_white);

  while(total_w <= inst->capacity && couple_id < inst->n_black && couple_id < inst->n_white) {
    assert((int)inst->n_black - (int)couple_id >= 0);
    assert((int)inst->n_white - (int)couple_id >= 0);
    
    uint_fast64_t weight_w = w_white[ids_white[inst->n_white - 1 - couple_id]];
    uint_fast64_t weight_b = w_black[ids_black[inst->n_black - 1 - couple_id]];
    
    if(total_w + weight_w + weight_b <= inst->capacity) {
      // Case 1:
      // Both items can be packed
      total_w += weight_w + weight_b;
      couple_id++;
    } else if(total_w + weight_w > inst->capacity && total_w + weight_b > inst->capacity) {
      // Case 2:
      // No other item can be packed
      FREE_ALL
      return (struct n_items_bound){.black = couple_id, .white = couple_id, .type = BOUND_FIXED};
    } else if(total_w + weight_w > inst->capacity && total_w + weight_b <= inst->capacity) {
      // Case 3:
      // We can pack the next black but not the next white item
      FREE_ALL
      return (struct n_items_bound){.black = couple_id + 1, .white = couple_id, .type = BOUND_FIXED};
    } else if(total_w + weight_w <= inst->capacity && total_w + weight_b > inst->capacity) {
      // Case 4:
      // We can pack the next white but not the next black item
      FREE_ALL
      return (struct n_items_bound){.black = couple_id, .white = couple_id + 1, .type = BOUND_FIXED};
    } else if(total_w + weight_w <= inst->capacity && total_w + weight_b <= inst->capacity) {
      // Case 5:
      // We can pack the next white or black item, but not both
      FREE_ALL
      return (struct n_items_bound){.black = couple_id, .white = couple_id, .type = BOUND_ANY};
    } else {
      // There should be no other case - for now! :)
      assert(false);
    }
    
    if(couple_id == inst->n_black && couple_id == inst->n_white) {
      // Case 6: we ran out of items (both black and white at the same time)
      FREE_ALL
      return (struct n_items_bound){.black = couple_id, .white = couple_id, .type = BOUND_FIXED};
    } else if(couple_id == inst->n_black && couple_id < inst->n_white) {
      // Case 7: we ran out of black items, but not of white items
      uint_fast64_t next_w = w_white[ids_white[inst->n_white - 1 - couple_id]];
      if(total_w + next_w <= inst->capacity) {
        // Case 7a: we can pack one more white item
        FREE_ALL
        return (struct n_items_bound){.black = couple_id, .white = couple_id + 1, .type = BOUND_FIXED};
      } else {
        // Case 7b: we cannot pack any more white items
        FREE_ALL
        return (struct n_items_bound){.black = couple_id, .white = couple_id, .type = BOUND_FIXED};
      }
    } else if(couple_id == inst->n_white && couple_id < inst->n_black) {
      // Case 8: we ran out of white items, but not of black items
      uint_fast64_t next_w = w_black[ids_black[inst->n_black - 1 - couple_id]];
      if(total_w + next_w <= inst->capacity) {
        // Case 8a: we can pack one more black item
        FREE_ALL
        return (struct n_items_bound){.black = couple_id + 1, .white = couple_id, .type = BOUND_FIXED};
      } else {
        // Case 8b: we cannot pack any more black items
        FREE_ALL
        return (struct n_items_bound){.black = couple_id, .white = couple_id, .type = BOUND_FIXED};
      }
    }
  }
  
  // We should never get here!
  FREE_ALL
  assert(false);
  return (struct n_items_bound){.black = 0, .white = 0, .type = 0};
}