#!/bin/sh
clear
ls *.c | while read filename;
do 
	cc ${filename} -lm -o $(echo ${filename} -ggdb | tr -d ".c")
done

exit 0
