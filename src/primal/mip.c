#include "mip.h"
#include "../timing.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ilcplex/cplex.h>

struct primal_solution solve_mip_primal(const struct instance* inst) {
  int status = 0;

  struct timespec start, end;
  get_monotonic_time(&start);

  CPXENVptr env;
  env = CPXopenCPLEX(&status);

  if(env == NULL) {
    printf("CPXopenCPLEX failed\n");
    exit(EXIT_FAILURE);
  }

  CPXLPptr lp;
  lp = CPXcreateprob(env, &status, "bwkp");

  if(lp == NULL) {
    printf("CPXcreateprob failed\n");
    exit(EXIT_FAILURE);
  }

  double obj[inst->n_items];
  double lb[inst->n_items];
  double ub[inst->n_items];
  char   type[inst->n_items];
  int    rmatbeg[3];
  int    rmatind[3 * inst->n_items];
  double rmatval[3 * inst->n_items];
  double rhs[3];
  char   sense[3];

  CPXchgobjsen(env, lp, CPX_MAX);

  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    obj[i] = inst->profits[i];
    lb[i] = 0;
    ub[i] = 1;
    type[i] = 'B';
  }

  status = CPXnewcols(env, lp, inst->n_items, obj, lb, ub, type, NULL);

  rmatbeg[0] = 0;
  rmatbeg[1] = inst->n_items;
  rmatbeg[2] = 2 * inst->n_items;

  rhs[0] = inst->capacity;
  rhs[1] = 1;
  rhs[2] = -1;

  sense[0] = 'L';
  sense[1] = 'L';
  sense[2] = 'G';

  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    rmatind[i] = i;
    rmatval[i] = inst->weights[i];

    rmatind[i + inst->n_items] = i;
    rmatval[i + inst->n_items] = (inst->colours[i] == BLACK ? 1 : -1);

    rmatind[i + 2 * inst->n_items] = i;
    rmatval[i + 2 * inst->n_items] = (inst->colours[i] == BLACK ? 1 : -1);
  }

  status = CPXaddrows(env, lp, 0, 3, 3 * inst->n_items, rhs, sense, rmatbeg, rmatind, rmatval, NULL, NULL);
  status = CPXsetdblparam(env, CPX_PARAM_TILIM, 300);
  status = CPXsetdblparam(env, CPX_PARAM_EPAGAP, 1e-12);
  status = CPXsetdblparam(env, CPX_PARAM_EPGAP, 0.0;
  status = CPXsetdblparam(env, CPX_PARAM_EPINT, 0.0);
  status = CPXsetdblparam(env, CPX_PARAM_EPOPT, 1e-9);
  status = CPXsetdblparam(env, CPX_PARAM_EPRHS, 1e-9);
  status = CPXsetintparam(env, CPX_PARAM_THREADS, 1);
  status = CPXmipopt(env, lp);

  get_monotonic_time(&end);

  int cur_ncols = CPXgetnumcols(env, lp);
  assert(cur_ncols == inst->n_items);

  double  profit;
  double* x;

  x = malloc(cur_ncols * sizeof(*x));

  if(x == NULL) {
    printf("Cannot allocate memory for LP solution\n");
    exit(EXIT_FAILURE);
  }

  status = CPXgetx(env, lp, x, 0, CPXgetnumcols(env, lp) - 1);

  if(status != 0) {
    printf("Cannot get CPLEX solution, status: %i\n", status);
    exit(EXIT_FAILURE);
  }

  status = CPXgetobjval(env, lp, &profit);

  if(status != 0) {
    printf("Cannot get CPLEX objective value, status: %i\n", status);
    exit(EXIT_FAILURE);
  }

  struct primal_solution sol = {
    .n_items = inst->n_items,
    .profit = profit,
    .used_capacity = 0.0,
    .e_time = get_elapsed_time_ms(&start, &end)
  };

  status = CPXgetmiprelgap(env, lp, &sol.gap);

  if(status != 0) {
    printf("Cannot get CPLEX MIP gap, status: %i\n", status);
    exit(EXIT_FAILURE);
  }

  sol.coeff = malloc(inst->n_items * sizeof(*(sol.coeff)));

  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    sol.coeff[i] = x[i];
    sol.used_capacity += x[i] * inst->weights[i];
  }

  free(x);
  CPXfreeprob(env, &lp);
  CPXcloseCPLEX(&env);

  return sol;
}