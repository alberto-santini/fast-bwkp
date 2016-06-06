#include "sort.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void heapsort_desc(const double* values, ptrdiff_t* ids, ptrdiff_t sz) {
  ptrdiff_t n = sz;
  ptrdiff_t i = sz / 2;
  ptrdiff_t parent;
  ptrdiff_t child;
  ptrdiff_t tmp;
  
  while(true) {
    if(i > 0) {
      tmp = ids[--i];
    } else {
      if(--n == 0) { return; }
      tmp = ids[n];
      ids[n] = ids[0];
    }
    
    parent = i;
    child = 2 * i + 1;
      
    while(child < n) {
      if(child < n - 1 && values[ids[child + 1]] < values[ids[child]]) { child++; }
      if(values[ids[child]] < values[tmp]) {
        ids[parent] = ids[child];
        parent = child;
        child = 2 * parent + 1;
      } else { break; }
    }
     
    ids[parent] = tmp;
  }
}


double* unique_desc(const double* values, ptrdiff_t sz, ptrdiff_t* unique_sz) {
  static const double eps = 1e-6;

  ptrdiff_t* ids;

  ids = malloc(sz * sizeof(*ids));
  if(ids == NULL) {
    printf("Cannot allocate memory for ids\n");
    exit(EXIT_FAILURE);
  }

  for(ptrdiff_t i = 0; i < sz; i++) { ids[i] = i; }

  heapsort_desc(values, ids, sz);

  double* unique;

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