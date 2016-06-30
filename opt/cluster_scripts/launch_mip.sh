#!/bin/bash

resultsdir="../../results"
exec="../../build/fast-bwkp"

mkdir -p ${resultsdir}

for dir in $(ls -d ../../data/*/)
do
    klass="$(basename ${dir})"
    outfile="${resultsdir}/${klass}.txt"
    scriptname="launch_${klass}.sh"
    
cat <<EOF >${scriptname}
#!/bin/bash
for f in ${dir}*.txt ; do ${exec} \${f} testmip ${outfile} ; done
EOF
    
    chmod u+x ${scriptname}    
    oarsub -n "${klass}" -O "${klass}.out" -E "${klass}.err" -p "network_address!='drbl10-201-201-21'" -l /nodes=1/core=1,walltime=12 "./${scriptname}"
done