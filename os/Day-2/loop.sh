#!/bin/bash
echo "Enter Limit"
read n
for(( i=1;i<n;i=i+2 ))
do
echo "$i"
done
