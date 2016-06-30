#!/bin/bash
for f in ../../data/similar_weights/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/similar_weights.txt ; done
