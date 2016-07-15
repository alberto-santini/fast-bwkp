#include "instance.h"
#include "relaxations/solution.h"
#include "relaxations/continuous.h"
#include "relaxations/lagrange.h"
#include "relaxations/cardinality_preserving.h"
#include "relaxations/capacity_preserving.h"
#include "primal/mip.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char** argv) {
  struct instance inst = read_instance(argv[1]);
  struct relaxation_solution sol;
  struct primal_solution psol;

  if(strcmp(argv[2], "desc") == 0) {
    printf("Instance description:\n");
    print_instance(&inst);
  } else if(strcmp(argv[2], "mip") == 0) {
    printf("Launching MIP solver\n");
    psol = solve_mip_primal(&inst);
    print_primal_solution(&psol);
    free_primal_solution(&psol);
  } else if(strcmp(argv[2], "lp") == 0) {
    printf("Launching continuous relaxation solver\n");
    sol = solve_continuous_relaxation(&inst);
    print_relaxation_solution(&sol);
    free_relaxation_solution(&sol);
  } else if(strcmp(argv[2], "lagr") == 0) {
    printf("Launching Lagrange relaxation solver\n");
    sol = solve_lagrange_relaxation(&inst);
    print_relaxation_solution(&sol);
    free_relaxation_solution(&sol);
  } else if(strcmp(argv[2], "cardp") == 0) {
    printf("Launching cardinality-preserving relaxation solver\n");
    sol = solve_cardinality_preserving_relaxation(&inst);
    print_relaxation_solution(&sol);
    free_relaxation_solution(&sol);
  } else if(strcmp(argv[2], "capp") == 0) {
    printf("Launching capacity-preserving relaxation solver\n");
    sol = solve_capacity_preserving_relaxation(&inst);
    print_relaxation_solution(&sol);
    free_relaxation_solution(&sol);
  } else if(strcmp(argv[2], "testrelax") == 0) {
    // --------- TEST ALL RELAXATIONS AND COMPARE WITH PRIMAL ---------
    FILE* fp;
    fp = fopen("results.txt", "a");

    if(fp == NULL) {
      printf("Can't open results file\n");
      exit(EXIT_FAILURE);
    }

    fprintf(fp, "%s,", argv[1]);
    write_instance_to_file(&inst, fp);
    
    sol = solve_continuous_relaxation(&inst);
    write_relaxation_solution_to_file(&sol, fp);

    sol = solve_lagrange_relaxation(&inst);
    write_relaxation_solution_to_file(&sol, fp);

    sol = solve_cardinality_preserving_relaxation(&inst);
    write_relaxation_solution_to_file(&sol, fp);

    sol = solve_capacity_preserving_relaxation(&inst);
    write_relaxation_solution_to_file(&sol, fp);

    psol = solve_mip_primal(&inst);
    write_primal_solution_to_file(&psol, fp);

    fprintf(fp, "\n");
    fclose(fp);
    free_relaxation_solution(&sol);
    free_primal_solution(&psol);
  } else if(strcmp(argv[2], "testlagr") == 0) {
    // --------- TEST LAGRANGE RELAXATION ---------
    FILE* fp;
    fp = fopen(argv[3], "a");
    
    if(fp == NULL) {
      printf("Can't open results file %s\n", argv[3]);
      exit(EXIT_FAILURE);
    }
    
    fprintf(fp, "%s,", argv[1]);
    write_instance_to_file(&inst, fp);
    
    sol = solve_lagrange_relaxation(&inst);
    write_relaxation_solution_to_file(&sol, fp);
    
    fprintf(fp, "\n");
    fclose(fp);
    free_relaxation_solution(&sol);
  } else if(strcmp(argv[2], "testmip") == 0) {
    // --------- CALCULATE PRIMAL SOLUTION WITH MIP ---------
    FILE* fp;
    fp = fopen(argv[3], "a");
    
    if(fp == NULL) {
      printf("Can't open results file %s\n", argv[3]);
      exit(EXIT_FAILURE);
    }
    
    fprintf(fp, "%s,", argv[1]);
    write_instance_to_file(&inst, fp);
    
    psol = solve_mip_primal(&inst);
    write_primal_solution_to_file(&psol, fp);
    
    fprintf(fp, "\n");
    fclose(fp);
    free_primal_solution(&psol);
  } else {
    printf("Command not recognised\n");
    exit(EXIT_FAILURE);
  }

  free_instance(&inst);
  return 0;
}