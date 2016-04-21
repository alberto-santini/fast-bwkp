#ifndef _LAGRANGE_H
#define _LAGRANGE_H

#include "instance.h"

struct lagrange_solution {
    float lagr_obj;
    int_fast32_t capacity_violation;
};

enum sorting_method {
    HEAPSORT,
    QUICKERSORT
};

// Returns the lagrangean objective value and the capacity violation;
// increments used_time_ms by the time it took, in milliseconds.
struct lagrange_solution solve_lagrange(const struct instance* inst, float multiplier, double* used_time_ms, enum sorting_method mtd);

// Retruns the min lagrangean objective value, among those found by using
// the p/w ratios (plus 0) as multipliers; saves in used_time_ms the time
// it took, in milliseconds.
struct lagrange_solution solve_for_all_pw(struct instance* inst, double* used_time_ms, enum sorting_method mtd);

#endif