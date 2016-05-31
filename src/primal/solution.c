#include "solution.h"
#include <stdlib.h>
#include <stdio.h>

void free_primal_solution(struct primal_solution* sol) {
  free(sol->coeff);
}

void print_primal_solution(const struct primal_solution* sol) {
  printf("Primal solution:\n");
  printf("\tTotal profit: %.4f\n", sol->profit);
  printf("\tUsed capacity: %.4f\n", sol->used_capacity);
  printf("\tTime (ms): %.4f\n", sol->e_time);
  printf("\tOptimality gap: %.4f", sol->gap);
  printf("\tChosen items in best integer solution:\n");
  for(ptrdiff_t i = 0; i < sol->n_items; i++) {
    if(sol->coeff[i] > 0) {
      printf("\t\t%td (%.4f)\n", i, sol->coeff[i]);
    }
  }
}

void write_primal_solution_to_file(const struct primal_solution* sol, FILE* fp) {
  fprintf(fp, "%.4f,%.4f,%.4f,%.10f,", sol->profit, sol->used_capacity, sol->e_time, sol->gap);
}