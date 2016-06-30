#!/bin/bash
for f in ../../data/circle/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/circle.txt ; done
