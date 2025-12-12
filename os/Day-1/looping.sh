#!/bin/bash
echo "Enter Limit"
read n
i=2
while [ $i -le $n ]
do
echo "$i"
i=`expr $i + 2`
done
