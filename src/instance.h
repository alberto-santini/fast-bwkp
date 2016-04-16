#ifndef _INSTANCE_H
#define _INSTANCE_H

#include <stdint.h>
#include <stddef.h>

enum colour_t { BLACK, WHITE };

struct instance {
    uint_fast32_t n_items;
    uint_fast32_t n_black;
    uint_fast32_t n_white;
    uint_fast32_t capacity;
    enum colour_t* colours;
    uint_fast32_t* weights;
    uint_fast32_t* profits;
    float* pws;
};

// Construct an instance from the data contained in
// filename. Returns the instance by value.
struct instance read_instance(const char* filename);

// Prints useful info on the instance to stdout.
void print_instance(const struct instance* inst);

// Deallocates dynamically-allocated arrays in the
// instance
void free_instance(struct instance* inst);

// Swaps two items in the order used to store their
// colours, weights, profits and p/w ratios.
void swap_items(struct instance* inst, ptrdiff_t i1, ptrdiff_t i2);

// Assuming that the instance is already sorted by p/w ratios,
// fills multipliers with the unique p/w ratios and sets
// n_multipliers to their number.
void get_unique_multipliers(struct instance* inst, float* multipliers, ptrdiff_t* n_multipliers);

#endif