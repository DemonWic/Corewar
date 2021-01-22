#!/bin/bash
for file in /Users/ahintz/Downloads/Corewar4/cmake-build-debug/champs/*
do
printf "\n $file \n"
sh test.sh $file
done