#!/bin/bash
echo "Insertion Sort"

gcc -std=c99 -o insertsort insertsort.c 
./insertsort > insert.txt
./insertsort
echo

echo "Merge Sort"
gcc -std=c99 -o mergesort mergesort.c 
./mergesort > merge.txt
./mergesort
echo
echo "Correctly sotred data"
cat sorted.txt
echo

diff -y -B -b --report-identical-files --suppress-common-lines insert.txt sorted.txt
echo
diff -y -B -b --report-identical-files --suppress-common-lines merge.txt sorted.txt
echo
echo "Insertion Sort times"
gcc -std=c99 -o insertTime insertTime.c 
./insertTime
echo
echo "Merge Sort times"
gcc -std=c99 -o mergeTime mergeTime.c 
./mergeTime

