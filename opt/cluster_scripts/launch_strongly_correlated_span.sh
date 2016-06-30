#!/bin/bash
for f in ../../data/strongly_correlated_span/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/strongly_correlated_span.txt ; done
