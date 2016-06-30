#!/bin/bash
for f in ../../data/almost_strongly_correlated/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/almost_strongly_correlated.txt ; done
