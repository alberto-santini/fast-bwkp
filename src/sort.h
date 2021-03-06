#ifndef _SORT_H
#define _SORT_H

#include <stdint.h>
#include <stddef.h>

// Given a vector of values and their indices ids = {0,...,sz-1}
// permutes the indices such that, at the end, values[ids[0]] will
// be the biggest element, ..., values[ids[sz-1]] the smallest.
void heapsort_desc(const double* values, ptrdiff_t* ids, ptrdiff_t sz);

// Given a vector of values, sorts them and discards any repeated
// element. It returns a new vector and does not modify the old one.
// It writes in unique_sz the number of elements in the returned vector.
double* unique_desc(const double* values, ptrdiff_t sz, ptrdiff_t* unique_sz);

#endif