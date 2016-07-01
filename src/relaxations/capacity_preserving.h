#ifndef _RELAXATION_CAPACITY_PRESERVING
#define _RELAXATION_CAPACITY_PRESERVING

#include "../instance.h"
#include "solution.h"

// Solves the capacity-preserving (i.e. Dantzig) relaxation of the problem described by inst
struct relaxation_solution solve_capacity_preserving_relaxation(const struct instance* inst);

#endif