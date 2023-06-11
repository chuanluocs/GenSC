#!/bin/bash
if [ $# -lt 1 ]; then
    echo "wrong argument"
    exit 1
fi

if [ $1 != "javagc" ] && [ $1 != "sac" ]; then
    echo "wrong argument"
    exit 1
fi
    
if [ ! -d $1 ]; then
    mkdir $1
fi
lc=`cat $1_SCP.txt | wc -l`
let pc=lc/20
i=1
while [ $i -le 20 ]; do
    let s=(i-1)*pc+1
    let e=i*pc
    if [ $i -eq 20 ]; then
        sed -n "${s}, \$p" $1_SCP.txt > $1/$1_$i.txt
    else
        sed -n "${s},${e}p" $1_SCP.txt > $1/$1_$i.txt
    fi
    let i++
done