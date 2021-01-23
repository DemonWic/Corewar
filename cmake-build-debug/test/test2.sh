#!/bin/bash
for file in /Users/ahintz/Downloads/Corewar7/cmake-build-debug/champs/*
do
printf "\n $file \n"
sh test.sh $file
done