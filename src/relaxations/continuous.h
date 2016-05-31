#ifndef _RELAXATION_CONTINUOUS_H
#define _RELAXATION_CONTINUOUS_H

#include "../instance.h"
#include "solution.h"

// Solves the continuous relaxation of the problem, using the model:
// max  sum_{i item} profit[i] * x[i]
// s.t. sum_{i item} weight[i] * x[i] <= capacity
//      -1 <= sum_{b black} x[b] - sum_{w white} x[w] <= 1
//      0 <= x[i] <= 1 for all i item
struct relaxation_solution solve_continuous_relaxation(const struct instance* inst);

#endif