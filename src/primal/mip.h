#ifndef _PRIMAL_MIP_H
#define _PRIMAL_MIP_H

#include "../instance.h"
#include "solution.h"

// Solves the MIP version of the problem, using the model:
// max  sum_{i item} profit[i] * x[i]
// s.t. sum_{i item} weight[i] * x[i] <= capacity
//      -1 <= sum_{b black} x[b] - sum_{w white} x[w] <= 1
//      x[i] binary for all i item
struct primal_solution solve_mip_primal(const struct instance* inst);

#endif