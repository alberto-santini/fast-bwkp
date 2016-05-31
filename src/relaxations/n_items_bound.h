#ifndef _RELAXATION_N_ITEMS_BOUND
#define _RELAXATION_N_ITEMS_BOUND

#include "../instance.h"

// Returns the maximum number K for which it is possible to pack K black *and*
// K white items, without violating the capacity constraint. Therefore, K+1
// is such that we cannot pack K+1 black and K+1 white items, but nothing can
// be said about the possibility of packing K black and K+1 white, or K white
// and K+1 black items.
uint_fast32_t get_capacity_bound(const struct instance* inst);

#endif