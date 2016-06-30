#!/bin/bash
for f in ../../data/strongly_correlated/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/strongly_correlated.txt ; done
