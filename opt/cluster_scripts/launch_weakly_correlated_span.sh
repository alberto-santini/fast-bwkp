#!/bin/bash
for f in ../../data/weakly_correlated_span/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/weakly_correlated_span.txt ; done
