#include "sort.h"
#include <stdbool.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include <float.h>

void in_place_heapsort_desc(float* sort_ary, uint_fast32_t* perm_ary, ptrdiff_t sz) {
    assert(sort_ary != NULL);
    assert(perm_ary != NULL);

    float t, pt;
    ptrdiff_t n = sz, parent = sz / 2, idx, child;

    #define ASSIGN_FROM_ARY(i) t = sort_ary[i]; pt = perm_ary[i];
    #define ASSIGN_TO_ARY(i) sort_ary[i] = t; perm_ary[i] = pt;
    #define ASSIGN_WITHIN_ARY(i, j) \
    sort_ary[i] = sort_ary[j]; \
    perm_ary[i] = perm_ary[j];

    while(true) {
        if(parent > 0) {
            parent--;
            ASSIGN_FROM_ARY(parent)
        } else {
            if(--n == 0) { return; }
            ASSIGN_FROM_ARY(n)
            ASSIGN_WITHIN_ARY(n, 0)
        }

        idx = parent;
        child = idx * 2 + 1;

        while(child < n) {
            if(child + 1 < n && sort_ary[child + 1] < sort_ary[child]) { child++; }
            if(sort_ary[child] < t) {
                ASSIGN_WITHIN_ARY(idx, child)
                idx = child;
                child = idx * 2 + 1;
            } else { break; }
        }
        ASSIGN_TO_ARY(idx)
    }
}

void in_place_heapsort_pw_asc(struct instance* inst) {
    assert(inst != NULL);

    enum colour_t t_col;
    float t_wgt, t_prf, t_pw;

    #define ASSIGN_FROM_INSTANCE(i) \
    t_col = inst->colours[i]; \
    t_wgt = inst->weights[i]; \
    t_prf = inst->profits[i]; \
    t_pw = inst->pws[i];

    #define ASSIGN_TO_INSTANCE(i) \
    inst->colours[i] = t_col; \
    inst->weights[i] = t_wgt; \
    inst->profits[i] = t_prf; \
    inst->pws[i] = t_pw;

    #define ASSIGN_WITHIN_INSTANCE(i, j) \
    inst->colours[i] = inst->colours[j]; \
    inst->weights[i] = inst->weights[j]; \
    inst->profits[i] = inst->profits[j]; \
    inst->pws[i] = inst->pws[j];

    ptrdiff_t n = inst->n_items;
    ptrdiff_t parent = n / 2;
    ptrdiff_t idx, child;

    while(true) {
        if(parent > 0) {
            parent--;
            ASSIGN_FROM_INSTANCE(parent)
        } else {
            if(--n == 0) { return; }
            ASSIGN_FROM_INSTANCE(n)
            ASSIGN_WITHIN_INSTANCE(n, 0)
        }

        idx = parent;
        child = idx * 2 + 1;

        while(child < n) {
            if(child + 1 < n && inst->pws[child + 1] > inst->pws[child]) { child++; }
            if(inst->pws[child] > t_pw) {
                ASSIGN_WITHIN_INSTANCE(idx, child)
                idx = child;
                child = idx * 2 + 1;
            } else { break; }
        }
        ASSIGN_TO_INSTANCE(idx)
    }
}

void in_place_quickersort_desc(float** sort_ary, uint_fast32_t** perm_ary, ptrdiff_t sz) {
        float* sort_enlarged = realloc(*sort_ary, (sz + 1) * sizeof(*sort_enlarged));
        assert(sort_enlarged != NULL);
        sort_enlarged[sz] = -FLT_MAX;

        uint_fast32_t* perm_enlarged = realloc(*perm_ary, (sz + 1) * sizeof(*perm_enlarged));
        assert(perm_enlarged != NULL);
        perm_enlarged[sz] = 0;

        in_place_quickersort_impl(sort_enlarged, perm_enlarged, 0, sz - 1);

        *sort_ary = realloc(sort_enlarged, sz * sizeof(**sort_ary));
        assert(*sort_ary != NULL);

        *perm_ary = realloc(perm_enlarged, sz * sizeof(**perm_ary));
        assert(*perm_ary != NULL);
}

void in_place_quickersort_impl(float* sort_ary, uint_fast32_t* perm_ary, ptrdiff_t lower, ptrdiff_t upper) {
    ptrdiff_t i, j;
    float sort_temp, pivot;
    uint_fast32_t perm_temp;

    #define SWAP(x, y) \
    sort_temp = sort_ary[x]; sort_ary[x] = sort_ary[y]; sort_ary[y] = sort_temp; \
    perm_temp = perm_ary[x]; perm_ary[x] = perm_ary[y]; perm_ary[y] = perm_temp;

    if(lower < upper) {
        SWAP(lower, (upper + lower)/2)
        i = lower;
        j = upper + 1;
        pivot = sort_ary[lower];

        while(true) {
	        do { i++; } while (sort_ary[i] > pivot);
            do { j--; } while (sort_ary[j] < pivot);
	        if (j < i) { break; }
	        SWAP(i, j);
	    }

	    SWAP(lower, j);
	    in_place_quickersort_impl(sort_ary, perm_ary, lower, j - 1);
	    in_place_quickersort_impl(sort_ary, perm_ary, i, upper);
    }
}