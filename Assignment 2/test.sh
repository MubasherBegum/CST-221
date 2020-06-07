#!/bin/bash
echo "UNIX Script"

echo "Command 1: cat testData.txt"
echo "========== output============"
cat testData.txt


echo "Command 2: find . -type f -name "*.sh""
echo "========== output============"
find . -type f -name "*.sh"


echo "Command 3: tail -n 5 testData.txt"
echo "========== output============"
tail -n 5 testData.txt


echo "Command 4: pwd"
echo "========== output============"
pwd


echo "Command 5: sort testData.txt | head -n 3"
echo "========== output============"
sort testData.txt | head -n 3
