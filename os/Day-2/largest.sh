#!/bin/bash
echo "Enter the first number"
read n1
echo "Enter the Second Number"
read n2
if [ $n1 -gt $n2 ]
then
echo "$n1 is largest "
elif [ $n1 -lt $n2 ]
then
echo "$n2 is largest"
else
echo "Both numbers are equal"
fi
