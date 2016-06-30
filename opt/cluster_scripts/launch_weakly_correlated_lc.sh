#!/bin/bash
for f in ../../data/weakly_correlated_lc/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/weakly_correlated_lc.txt ; done
