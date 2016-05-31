#include "sort.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SWAP(x,y) tmp = x; x = y; y = tmp;

void sift_desc(const float* values, ptrdiff_t* ids, ptrdiff_t root, ptrdiff_t last) {
  ptrdiff_t mchild, tmp;

  while(2 * root <= last) {
    if(2 * root == last) { mchild = last; }
    else if(values[ids[2 * root]] < values[ids[2 * root + 1]]) { mchild = 2 * root; }
    else { mchild = 2 * root + 1; }

    if(values[ids[root]] > values[ids[mchild]]) {
      SWAP(ids[root], ids[mchild])
      root = mchild;
    } else { break; }
  }
}

void heapsort_desc(const float* values, ptrdiff_t* ids, ptrdiff_t sz) {
  ptrdiff_t tmp;

  for(ptrdiff_t i = sz / 2 - 1; i >= 0; i--) { sift_desc(values, ids, i, sz - 1); }
  for(ptrdiff_t i = sz - 1; i >= 1; i--) {
    SWAP(ids[0], ids[i])
    sift_desc(values, ids, 0, i - 1);
  }
}

float* unique_desc(const float* values, ptrdiff_t sz, ptrdiff_t* unique_sz) {
  static const float eps = 1e-6;

  ptrdiff_t* ids;

  ids = malloc(sz * sizeof(*ids));
  if(ids == NULL) {
    printf("Cannot allocate memory for ids\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < sz; i++) { ids[i] = i; }

  heapsort_desc(values, ids, sz);

  float* unique;

  unique = malloc(sz * sizeof(*unique));
  if(unique == NULL) {
    printf("Cannot allocate memory for unique\n");
    exit(EXIT_FAILURE);
  }

  unique[0] = values[ids[0]];
  *unique_sz = 1;

  for(ptrdiff_t i = 1; i < sz; i++) {
    if(values[ids[i]] < unique[*unique_sz - 1] - eps) {
      unique[(*unique_sz)++] = values[ids[i]];
    }
  }

  return unique;
}