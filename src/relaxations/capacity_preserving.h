#ifndef _RELAXATION_CAPACITY_PRESERVING
#define _RELAXATION_CAPACITY_PRESERVING

#include "../instance.h"
#include "solution.h"

// Solves the capacity-preserving relaxation of the problem described by inst
struct relaxation_solution solve_capacity_preserving_relaxation(const struct instance* inst);

// Solves the capacity-preserving relaxation, when we are allowed to take at most
// maxb black and maxw white items. Vector ids contains items' indeces sorted by p/w
struct relaxation_solution solve_capacity_preserving_relaxation_for_bounds(const struct instance* inst, uint_fast32_t maxb, uint_fast32_t maxw, const ptrdiff_t* ids);

#endif