#!/bin/bash
for f in ../../data/bounded_strongly_correlated/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/bounded_strongly_correlated.txt ; done
