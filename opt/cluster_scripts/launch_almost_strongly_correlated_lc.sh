#!/bin/bash
for f in ../../data/almost_strongly_correlated_lc/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/almost_strongly_correlated_lc.txt ; done
