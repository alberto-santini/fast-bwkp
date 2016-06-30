#!/bin/bash
for f in ../../data/weakly_correlated/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/weakly_correlated.txt ; done
