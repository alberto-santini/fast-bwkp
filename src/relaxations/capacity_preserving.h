#ifndef _RELAXATION_CAPACITY_PRESERVING
#define _RELAXATION_CAPACITY_PRESERVING

#include "../instance.h"
#include "solution.h"

// Solves the capacity-preserving relaxation of the problem described by inst
struct relaxation_solution solve_capacity_preserving_relaxation(const struct instance* inst);

// Solves the capacity-preserving relaxation, when we are allowed to take at most
// maxi items. Vector ids contains items' indeces sorted by p/w
struct relaxation_solution solve_capacity_preserving_relaxation_for_bound(const struct instance* inst, uint_fast32_t maxi, const ptrdiff_t* ids);

#endif