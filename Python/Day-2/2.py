#Write a program to find the largest of three numbers using the ‘if’ statement.
num1=float(input("First Digit : "))
num2=float(input("Second Digit : "))
num3=float(input("Third Digit : "))

if (num1 > num2 and num1 > num3):
    print(f"{num1} is the Greatest")
elif (num2 > num3 and num2 > num1):
    print(f"{num2} is the Greatest")
else :
    print(f"{num3} is the Greatest")
