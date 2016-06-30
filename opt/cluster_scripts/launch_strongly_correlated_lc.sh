#!/bin/bash
for f in ../../data/strongly_correlated_lc/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/strongly_correlated_lc.txt ; done
