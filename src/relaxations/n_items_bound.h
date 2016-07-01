#ifndef _RELAXATION_N_ITEMS_BOUND
#define _RELAXATION_N_ITEMS_BOUND

#include "../instance.h"

// Tells which type of bound we are dealing with:
// - a FIXED bound tells us that we should pack exactly ``black''
//   black and ``white'' white items.
// - an ANY bound, tells us that we should try to pack both
//   ``black'' black and ``white + 1'' white items, and ``black + 1''
//   black and ``white'' white items.
enum n_items_bound_type {
    BOUND_FIXED,
    BOUND_ANY
};

// Represents a bound on the number of objects that can be packed.
struct n_items_bound {
    // Number of black objects
    ptrdiff_t black;
    // Number of white objects
    ptrdiff_t white;
    // Bound type
    enum n_items_bound_type type;
};

// Returns a bound on the number of objects that can be packed, based
// on their capacities.
struct n_items_bound get_capacity_bound(const struct instance* inst);

#endif