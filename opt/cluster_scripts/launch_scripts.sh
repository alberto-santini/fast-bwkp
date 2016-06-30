#!/bin/bash
for f in ../../data/scripts/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/scripts.txt ; done
