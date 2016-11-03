#! /bin/bash

count=$1
ip=$2
port=$3

if [ $# -lt 3 ]; then
    echo "$cstestpath/autoClient.sh count ip port"
    exit 1
fi

for((i=1; i<=$count; i++))
do
    ./c_s_test/c $ip $port &
done

echo "$count done"
