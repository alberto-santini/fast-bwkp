#!/bin/bash
for f in ../../data/uncorrelated_span/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/uncorrelated_span.txt ; done
