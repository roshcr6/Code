#Write a program that takes an integer as input and
#calculates the sum of its digits using a ‘while’ loop.
num = int(input("Enter an integer: "))
sum_digits = 0

num = abs(num)  
while num > 0:
    digit = num % 10
    sum_digits += digit
    num //= 10

print("Sum of digits:", sum_digits)
