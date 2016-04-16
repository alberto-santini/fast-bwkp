#include "lagrange.h"
#include "timing.h"
#include "sort.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct lagrange_solution solve_lagrange(const struct instance* inst, float multiplier, double* used_time_ms) {
    assert(inst != NULL);
    
    struct timespec start, end;
    get_monotonic_time(&start);
    
    float* lagr_p_black;
    float* lagr_p_white;
    uint_fast32_t* w_black;
    uint_fast32_t* w_white;
    
    lagr_p_black = malloc(inst->n_black * sizeof(*lagr_p_black));
    assert(lagr_p_black != NULL);
    
    lagr_p_white = malloc(inst->n_white * sizeof(*lagr_p_white));
    assert(lagr_p_white != NULL);
    
    w_black = malloc(inst->n_black * sizeof(*w_black));
    assert(w_black != NULL);
    
    w_white = malloc(inst->n_white * sizeof(*w_white));
    assert(w_white != NULL);
    
    ptrdiff_t i_black = 0, i_white = 0;
    
    for(ptrdiff_t i = 0; i < inst->n_items; i++) {
        float lagr_profit = inst->profits[i] - multiplier * inst->weights[i];
        
        if(inst->colours[i] == BLACK) {
            lagr_p_black[i_black] = lagr_profit;
            w_black[i_black] = inst->weights[i];
            i_black++;
        } else {
            lagr_p_white[i_white] = lagr_profit;
            w_white[i_white] = inst->weights[i];
            i_white++;
        }
    }
    
    in_place_heapsort_desc(lagr_p_black, w_black, inst->n_black);
    in_place_heapsort_desc(lagr_p_white, w_white, inst->n_white);
    
    i_black = 0;
    i_white = 0;
    
    float lagr_obj = multiplier * (float)inst->capacity;
    uint_fast32_t used_capacity = 0;
    
    
    while(i_black < inst->n_black && i_white < inst->n_white) {
        if(lagr_p_black[i_black] + lagr_p_white[i_white] >= 0) {
            lagr_obj += lagr_p_black[i_black] + lagr_p_white[i_white];
            used_capacity += w_black[i_black] + w_white[i_white];
        } else {
            if(lagr_p_black[i_black] >= 0) {
                lagr_obj += lagr_p_black[i_black];
                used_capacity += w_black[i_black];
            }
            if(lagr_p_white[i_white] >= 0) {
                lagr_obj += lagr_p_white[i_white];
                used_capacity += w_white[i_white];
            }
            break;
        }
        
        i_black++;
        i_white++;
        
        if(i_white == inst->n_white && i_black < inst->n_black) {
            if(lagr_p_black[i_black] >= 0) {
                lagr_obj += lagr_p_black[i_black];
                used_capacity += w_black[i_black];
            }
            break;
        }
        
        if(i_black == inst->n_black && i_white < inst->n_white) {
            if(lagr_p_white[i_white] >= 0) {
                lagr_obj += lagr_p_white[i_white];
                used_capacity += w_white[i_white];
            }
            break;
        }
    }
    
    get_monotonic_time(&end);
    *used_time_ms += get_elapsed_time_ms(&start, &end);
    
    struct lagrange_solution sol;
    
    sol.lagr_obj = lagr_obj;
    sol.capacity_violation = (int_fast32_t)used_capacity - (int_fast32_t)inst->capacity;
    
    free(lagr_p_black);
    free(lagr_p_white);
    free(w_black);
    free(w_white);
    
    return sol;
}

struct lagrange_solution solve_for_all_pw(struct instance* inst, double* used_time_ms) {
    assert(inst != NULL);
    
    float* multipliers;
    ptrdiff_t n_multipliers;
    
    multipliers = malloc(inst->n_items * sizeof(*multipliers));
    assert(multipliers != NULL);
    
    in_place_heapsort_pw_asc(inst);
    get_unique_multipliers(inst, multipliers, &n_multipliers);
    
    *used_time_ms = 0;
    
    struct lagrange_solution sol = solve_lagrange(inst, 0.0, used_time_ms);
    
    if(sol.capacity_violation <= 0) { return sol; }
    
    struct lagrange_solution best = sol;
    
    for(ptrdiff_t i = 0; i < n_multipliers && sol.capacity_violation >= 0; i++) {
        sol = solve_lagrange(inst, multipliers[i], used_time_ms);
        if(sol.lagr_obj < best.lagr_obj) { best = sol; }
    }
    
    free(multipliers);
    
    return best;
}