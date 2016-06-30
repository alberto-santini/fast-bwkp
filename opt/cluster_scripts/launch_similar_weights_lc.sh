#!/bin/bash
for f in ../../data/similar_weights_lc/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/similar_weights_lc.txt ; done
