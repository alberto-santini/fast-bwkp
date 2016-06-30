#!/bin/bash
for f in ../../data/mstr/*.txt ; do ../../build/fast-bwkp ${f} testmip ../../results/mstr.txt ; done
