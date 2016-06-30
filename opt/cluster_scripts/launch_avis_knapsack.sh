#!/bin/bash
for f in ../../data/avis_knapsack/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/avis_knapsack.txt ; done
