#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 <prob_number>"
    exit 1
fi

RED='\033[0;31m'
GREEN='\033[0;32m'

for i in ../tests/$1/*
do
    Input=$(cat $i | ./getInput.sh)
    Output=$(cat $i | ./getOutput.sh)
    ResTest=$(echo ${Input} | ./$1/c/main)

    if [[ ${Output} != ${ResTest} ]]
    then
        echo -e "${RED}$i failed"
        echo "OUTPUT: ${Output}"
        echo "RESTEST: ${ResTest}"
    else
        echo -e "${GREEN}$i passed"
    fi
done
