#!/bin/bash
echo "Knapsack DP vs Recursive"
gcc -std=c99 -o knapsack knapsack.c 
./knapsack

echo "Shopping Spree"
echo

gcc -std=c99 -o shopping shopping.c 
./shopping > my_results.txt
./shopping

echo "Comparing results "
diff -y -B -b --report-identical-files --suppress-common-lines my_results.txt HW2Solution.txt
echo


