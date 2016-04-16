#ifndef _SORT_H
#define _SORT_H

#include <stdint.h>
#include <stddef.h>
#include "instance.h"

// Sorts a vector of floats in-place, and permutes a
// second vector accordingly.
void in_place_heapsort_desc(float* sort_ary, uint_fast32_t* perm_ary, ptrdiff_t sz);

// Orders the items in the instance by p/w ratios,
// changing by the same permutation also the
// vectors with colours, weights, and profits.
void in_place_heapsort_pw_asc(struct instance* inst);

#endif