#include "solution.h"
#include <stdlib.h>
#include <stdio.h>

void free_relaxation_solution(struct relaxation_solution* sol) {
  free(sol->coeff);
}

void print_relaxation_solution(const struct relaxation_solution* sol) {
  printf("Relaxation solution:\n");
  printf("\tTotal profit: %.4f\n", sol->profit);
  printf("\tBound: %.4f\n", sol->bound);
  printf("\tUsed capacity: %.4f\n", sol->used_capacity);
  printf("\tTime (ms): %.4f\n", sol->e_time);
  printf("\tExtra param: %.4f\n", sol->param);
  printf("\tChosen items:\n");
  for(ptrdiff_t i = 0; i < sol->n_items; i++) {
    if(sol->coeff[i] > 0) {
      printf("\t\t%td (%.4f)\n", i, sol->coeff[i]);
    }
  }
}

void write_relaxation_solution_to_file(const struct relaxation_solution* sol, FILE* fp) {
  fprintf(fp, "%.4f,%.4f,%.4f,", sol->bound, sol->used_capacity, sol->e_time);
}

struct relaxation_solution deep_copy_relaxation_solution(const struct relaxation_solution* sol) {
  struct relaxation_solution newsol = {
    .n_items = sol->n_items,
    .profit = sol->profit,
    .used_capacity = sol->used_capacity,
    .e_time = sol->e_time,
    .bound = sol->bound,
    .param = sol->param
  };
  
  newsol.coeff = malloc(newsol.n_items * sizeof(*(newsol.coeff)));
  if(newsol.coeff == NULL) {
    printf("Cannot allocate memory to copy relaxation solution\n");
    exit(EXIT_FAILURE);
  }
  
  for(ptrdiff_t i = 0; i < newsol.n_items; i++) {
    newsol.coeff[i] = sol->coeff[i];
  }
  
  return newsol;
}