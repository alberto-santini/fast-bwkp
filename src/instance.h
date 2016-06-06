#ifndef _INSTANCE_H
#define _INSTANCE_H

#include <stdint.h>
#include <stddef.h>

enum colour_t { BLACK, WHITE };

struct instance {
  // Total number of items
  uint_fast32_t n_items;

  // Number of black items
  uint_fast32_t n_black;

  // Number of white items
  uint_fast32_t n_white;

  // Total bin capacity
  uint_fast32_t capacity;

  // Vector of weights, one for each item
  uint_fast32_t* weights;

  // Vector of profits, one for each items
  uint_fast32_t* profits;

  // Vector of colours, one for each item
  enum colour_t* colours;

  // For convenience, we store in this vector
  // the profit/weight ratios, one for each item
  double* pws;
};

// Construct an instance from the data contained in
// filename. Returns the instance by value.
struct instance read_instance(const char* filename);

// Prints useful info on the instance to stdout.
void print_instance(const struct instance* inst);

// Deallocates dynamically-allocated arrays in the
// instance
void free_instance(struct instance* inst);

#endif