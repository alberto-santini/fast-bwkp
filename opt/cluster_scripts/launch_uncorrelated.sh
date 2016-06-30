#!/bin/bash
for f in ../../data/uncorrelated/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/uncorrelated.txt ; done
