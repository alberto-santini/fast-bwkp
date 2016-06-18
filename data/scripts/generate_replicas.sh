#!/usr/bin/env bash

cd /Users/alberto/Dropbox/Documents/PhD/BWBP/Instances

while read i
do
    components=(${i//_/ })
    ./pisinger_generator.rb pisinger_hard/${components[2]}_${components[3]}_${components[4]}_${components[5]}.csv ${components[1]}
    cp ./bw_inst/${i}.json ~/Programming/bwbp/data/from_david/mip_difficult_replica/
done < ~/Desktop/diff.txt