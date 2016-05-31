#ifndef _RELAXATION_CARDINALITY_PRESERVING_H
#define _RELAXATION_CARDINALITY_PRESERVING_H

#include "../instance.h"
#include "solution.h"

// Solves the cardinality-preserving relaxation of the problem described by inst
struct relaxation_solution solve_cardinality_preserving_relaxation(const struct instance* inst);

// Solves the cardinality-preserving relaxation, when we are allowed to take at most
// maxb black and maxw white items. Vector ids contains items' indeces sorted by p/w
struct relaxation_solution solve_cardinality_preserving_relaxation_for_bounds(const struct instance* inst, uint_fast32_t maxb, uint_fast32_t maxw, const ptrdiff_t* ids);

#endif