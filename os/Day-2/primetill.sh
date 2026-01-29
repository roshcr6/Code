#!/bin/bash
echo -n "Enter the primes from : "
read low
echo -n "Enter the primes till: "
read top

for (( num=low; num<=top; num++ ))
do
    isPrime=1   
    for (( i=2; i<num; i++ ))
    do
        if [ $((num%i)) -eq 0 ]; then
            isPrime=0
            break
        fi
    done

    if [ $isPrime -eq 1 ] && [ $num -gt 1 ]; then
        echo "$num"
    fi
done

