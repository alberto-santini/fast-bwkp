#!/bin/bash
for f in ../../data/uncorrelated_lc/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/uncorrelated_lc.txt ; done
