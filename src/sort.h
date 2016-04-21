#ifndef _SORT_H
#define _SORT_H

#include <stdint.h>
#include <stddef.h>
#include "instance.h"

// Sorts a vector of floats in-place, and permutes a
// second vector accordingly.
void in_place_heapsort_desc(float* sort_ary, uint_fast32_t* perm_ary, ptrdiff_t sz);

// Sorts a vector of floats in-place, and permutes a
// second vector accordingly.
void in_place_quickersort_desc(float** sort_ary, uint_fast32_t** perm_ary, ptrdiff_t sz);
void in_place_quickersort_impl(float* sort_ary, uint_fast32_t* perm_ary, ptrdiff_t lower, ptrdiff_t upper);

// Orders the items in the instance by p/w ratios,
// changing by the same permutation also the
// vectors with colours, weights, and profits.
void in_place_heapsort_pw_asc(struct instance* inst);

void print(const float* sv, const uint_fast32_t* pv, ptrdiff_t sz);

#endif