#include "instance.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct instance read_instance(const char* filename) {
    FILE* fd;
    
    fd = fopen(filename, "r");
    
    if(fd == NULL) {
        printf("Cannot read %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    struct instance inst;
    int n_read;
    
    n_read = fscanf(fd, "%u %u %u %u", &inst.n_items, &inst.n_black, &inst.n_white, &inst.capacity);
    
    if(n_read != 4) {
        printf("Error reading the for initial values\n");
        exit(EXIT_FAILURE);
    }
    
    if(inst.n_items == 0) {
        printf("I would prefer an instance with >0 items\n");
        exit(EXIT_FAILURE);
    }
    
    if(inst.n_black > inst.n_items) {
        printf( "Number of black items (%d) cannot be bigger than the total number of items (%d)\n",
                inst.n_black, inst.n_items);
        exit(EXIT_FAILURE);
    }
    
    if(inst.n_white > inst.n_items) {
        printf( "Number of white items (%d) cannot be bigger than the total number of items (%d)\n",
                inst.n_white, inst.n_items);
        exit(EXIT_FAILURE);
    }
    
    if(inst.n_black + inst.n_white != inst.n_items) {
        printf("Number of black + white items should be equal to total number of items\n");
        exit(EXIT_FAILURE);
    }
    
    inst.colours = malloc(inst.n_items * sizeof(*inst.colours));
    
    if(inst.colours == NULL) {
        printf("Could not allocate memory for the colours vector\n");
        exit(EXIT_FAILURE);
    }
    
    inst.weights = malloc(inst.n_items * sizeof(*inst.weights));
    
    if(inst.weights == NULL) {
        printf("Could not allocate memory for the weights vector\n");
        exit(EXIT_FAILURE);
    }
    
    inst.profits = malloc(inst.n_items * sizeof(*inst.profits));
    
    if(inst.profits == NULL) {
        printf("Could not allocate memory for the profits vector\n");
        exit(EXIT_FAILURE);
    }
    
    inst.pws = malloc(inst.n_items * sizeof(*inst.pws));
    
    if(inst.pws == NULL) {
        printf("Could not allocate memory for the p/w vector\n");
        exit(EXIT_FAILURE);
    }
    
    for(ptrdiff_t i = 0; i < inst.n_items; i++) {
        char colour;
        n_read = fscanf(fd, " %c", &colour);
        
        if(n_read != 1) {
            printf("Error reading colours\n");
            exit(EXIT_FAILURE);
        }
        
        if(colour == 'b') {
            inst.colours[i] = BLACK;
        } else if(colour == 'w') {
            inst.colours[i] = WHITE;
        } else {
            printf("Invalid colour: %c\n", colour);
            exit(EXIT_FAILURE);
        }
    }
    
    for(ptrdiff_t i = 0; i < inst.n_items; i++) {
        n_read = fscanf(fd, "%u", &inst.weights[i]);
        
        if(n_read != 1) {
            printf("Error reading weights\n");
            exit(EXIT_FAILURE);
        }
    }
    
    for(ptrdiff_t i = 0; i < inst.n_items; i++) {
        n_read = fscanf(fd, "%u", &inst.profits[i]);
        
        if(n_read != 1) {
            printf("Error reading profits\n");
            exit(EXIT_FAILURE);
        }
        
        inst.pws[i] = (float)inst.profits[i] / (float)inst.weights[i];
    }
    
    if(fclose(fd) != 0) {
        printf("Error closing file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    return inst;
}

void print_instance(const struct instance* inst) {
    printf("Number of items: %u (%u black and %u white)\n", inst->n_items, inst->n_black, inst->n_white);
    printf("Item weights: ");
    for(ptrdiff_t i = 0; i < inst->n_items; i++) {
        printf("%u, ", inst->weights[i]);
    }
    printf("\nItem profits: ");
    for(ptrdiff_t i = 0; i < inst->n_items; i++) {
        printf("%u, ", inst->profits[i]);
    }
    printf("\nItem colours: ");
    for(ptrdiff_t i = 0; i < inst->n_items; i++) {
        printf("%c, ", inst->colours[i] == BLACK ? 'b' : 'w');
    }
    printf("\nItem p/w ratios: ");
    for(ptrdiff_t i = 0; i < inst->n_items; i++) {
        printf("%.3f, ", inst->pws[i]);
    }
    printf("\n");
}

void free_instance(struct instance* inst) {
    free(inst->colours); inst->colours = NULL;
    free(inst->weights); inst->weights = NULL;
    free(inst->profits); inst->profits = NULL;
    free(inst->pws); inst->pws = NULL;
}

void swap_items(struct instance* inst, ptrdiff_t i1, ptrdiff_t i2) {
    assert(0 <= i1); assert(i1 < inst->n_items);
    assert(0 <= i2); assert(i2 < inst->n_items);
    
    enum colour_t t_col;
    t_col = inst->colours[i1];
    inst->colours[i1] = inst->colours[i2];
    inst->colours[i2] = t_col;
    
    uint_fast32_t t_wgt;
    t_wgt = inst->weights[i1];
    inst->weights[i1] = inst->weights[i2];
    inst->weights[i2] = t_wgt;
            
    uint_fast32_t t_prf;
    t_prf = inst->profits[i1];
    inst->profits[i1] = inst->profits[i2];
    inst->profits[i2] = t_prf;
    
    float t_pw;
    t_pw = inst->pws[i1];
    inst->pws[i1] = inst->pws[i2];
    inst->pws[i2] = t_pw;
}

void get_unique_multipliers(struct instance* inst, float* multipliers, ptrdiff_t* n_multipliers) {
    assert(inst != NULL);
    assert(multipliers != NULL);
    assert(n_multipliers != NULL);
    
    static const float eps = 1e-6;
    
    multipliers[0] = inst->pws[0];
    *n_multipliers = 1;
    
    for(ptrdiff_t i = 1; i < inst->n_items; i++) {
        if(fabsf(inst->pws[i] - multipliers[*n_multipliers - 1]) > eps) {
            multipliers[(*n_multipliers)++] = inst->pws[i];
        }
    }
}