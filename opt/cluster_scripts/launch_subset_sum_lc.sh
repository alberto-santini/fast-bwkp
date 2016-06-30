#!/bin/bash
for f in ../../data/subset_sum_lc/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/subset_sum_lc.txt ; done
