#!/bin/bash
for f in ../../data/avis_subset_sum/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/avis_subset_sum.txt ; done
