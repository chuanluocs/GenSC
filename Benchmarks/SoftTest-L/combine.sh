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
    echo "no such directory"
    exit 1
fi

i=1
while [ $i -le 20 ]; do
    cat $1/$1_$i.txt >> $1_SCP.txt
    let i++
done