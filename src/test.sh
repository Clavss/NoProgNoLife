#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 <prob_number>"
    exit 1
fi

for i in ../tests/$1/*
do
    Input=$(cat $i | ./getInput.sh)
    Output=$(cat $i | ./getOutput.sh)
    ResTest=$(echo ${Input} | ./$1/main)

    if [ ${ResTest} != ${Output} ]
    then
        echo "$i failed"
    else
        echo "$i passed"
    fi
done