#!/bin/bash
for f in ../../data/pceil/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/pceil.txt ; done
