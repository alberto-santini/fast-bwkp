#!/bin/bash
for f in ../../data/no_small_weights/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/no_small_weights.txt ; done
