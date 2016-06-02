#include "instance.h"
#include <inttypes.h>
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

  n_read = fscanf(fd, "%" SCNuFAST32 " %" SCNuFAST32 " %" SCNuFAST32 " %" SCNuFAST32, &inst.n_items, &inst.n_black, &inst.n_white, &inst.capacity);

  if(n_read != 4) {
    printf("Error reading the for initial values\n");
    exit(EXIT_FAILURE);
  }

  if(inst.n_items == 0) {
    printf("I would prefer an instance with >0 items\n");
    exit(EXIT_FAILURE);
  }

  if(inst.n_black > inst.n_items) {
    printf( "Number of black items (%" SCNuFAST32 ") cannot be bigger than the total number of items (%" SCNuFAST32 ")\n",
            inst.n_black, inst.n_items);
    exit(EXIT_FAILURE);
  }

  if(inst.n_white > inst.n_items) {
    printf( "Number of white items (%" SCNuFAST32 ") cannot be bigger than the total number of items (%" SCNuFAST32 ")\n",
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
    n_read = fscanf(fd, "%" SCNuFAST32, &inst.weights[i]);

    if(n_read != 1) {
      printf("Error reading weights\n");
      exit(EXIT_FAILURE);
    }
  }

  for(ptrdiff_t i = 0; i < inst.n_items; i++) {
    n_read = fscanf(fd, "%" SCNuFAST32, &inst.profits[i]);

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
  printf("Number of items: %" PRIuFAST32 " (%" PRIuFAST32 " black and %" PRIuFAST32 " white)\n",
          inst->n_items, inst->n_black, inst->n_white);
  printf("Capacity: %" PRIuFAST32 "\n", inst->capacity);
  printf("\tItem weights:\n");
  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    printf("\t%td: %" PRIuFAST32 "\n", i, inst->weights[i]);
  }
  printf("\nItem profits:\n");
  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    printf("\t%td: %" PRIuFAST32 "\n", i, inst->profits[i]);
  }
  printf("\nItem colours:\n");
  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    printf("\t%td: %c\n", i, inst->colours[i] == BLACK ? 'b' : 'w');
  }
  printf("\nItem p/w ratios:\n");
  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    printf("\t%td: %.4f\n", i, inst->pws[i]);
  }
  printf("\n");
}

void free_instance(struct instance* inst) {
  free(inst->colours); inst->colours = NULL;
  free(inst->weights); inst->weights = NULL;
  free(inst->profits); inst->profits = NULL;
  free(inst->pws); inst->pws = NULL;
}