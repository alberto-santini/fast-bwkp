#!/bin/bash
for f in ../../data/inverse_strongly_correlated/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/inverse_strongly_correlated.txt ; done
