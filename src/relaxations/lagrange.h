#ifndef _RELAXATION_LAGRANGE_H
#define _RELAXATION_LAGRANGE_H

#include <stddef.h>
#include "../instance.h"
#include "solution.h"

// Gives the best lagrange relaxation solution for instance inst, among the ones that use
// 0 and all the p/w values as multipliers.
struct relaxation_solution solve_lagrange_relaxation(const struct instance* inst);

// Gives the lagrange relaxation solution for instance ins, using a certain multiplier.
// It puts the lagrange objective value in lagr_obj.
struct relaxation_solution solve_lagrange_for_multiplier(const struct instance* inst, double multiplier);

#endif