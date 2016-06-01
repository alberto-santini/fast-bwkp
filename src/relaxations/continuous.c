#include "continuous.h"
#include "../timing.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ilcplex/cplex.h>

struct relaxation_solution solve_continuous_relaxation(const struct instance* inst) {
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
  }

  status = CPXnewcols(env, lp, inst->n_items, obj, lb, ub, NULL, NULL);

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
  status = CPXsetdblparam(env, CPX_PARAM_EPOPT, 1e-9);
  status = CPXsetdblparam(env, CPX_PARAM_EPRHS, 1e-9);
  status = CPXlpopt(env, lp);

  get_monotonic_time(&end);

  int cur_nrows = CPXgetnumrows(env, lp);
  int cur_ncols = CPXgetnumcols(env, lp);

  assert(cur_nrows == 3);
  assert(cur_ncols == inst->n_items);

  int     solstat;
  double  profit;
  double* x;
  double* pi;
  double* slack;
  double* dj;

  x = malloc(cur_ncols * sizeof(*x));
  pi = malloc(cur_nrows * sizeof(*pi));
  slack = malloc(cur_nrows * sizeof(*slack));
  dj = malloc(cur_ncols * sizeof(*dj));

  if(x == NULL || pi == NULL || slack == NULL || dj == NULL) {
    printf("Cannot allocate memory for LP solution\n");
    exit(EXIT_FAILURE);
  }

  status = CPXsolution(env, lp, &solstat, &profit, x, pi, slack, dj);

  if(status != 0) {
    printf("Cannot get CPLEX solution, status: %i\n", status);
    exit(EXIT_FAILURE);
  }

  struct relaxation_solution sol = {
    .n_items = inst->n_items,
    .profit = profit,
    .bound = profit,
    .param = 0.0,
    .used_capacity = 0.0,
    .e_time = get_elapsed_time_ms(&start, &end)
  };

  sol.coeff = malloc(inst->n_items * sizeof(*(sol.coeff)));

  for(ptrdiff_t i = 0; i < inst->n_items; i++) {
    sol.coeff[i] = x[i];
    sol.used_capacity += x[i] * inst->weights[i];
  }

  free(x);
  free(pi);
  free(slack);
  free(dj);
  CPXfreeprob(env, &lp);
  CPXcloseCPLEX(&env);

  return sol;
}