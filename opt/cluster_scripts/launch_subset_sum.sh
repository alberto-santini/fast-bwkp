#!/bin/bash
for f in ../../data/subset_sum/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/subset_sum.txt ; done
