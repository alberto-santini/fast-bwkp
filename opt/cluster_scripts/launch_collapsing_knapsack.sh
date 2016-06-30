#!/bin/bash
for f in ../../data/collapsing_knapsack/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/collapsing_knapsack.txt ; done
