#!/bin/bash
for f in ../../data/inverse_strongly_correlated_lc/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/inverse_strongly_correlated_lc.txt ; done
