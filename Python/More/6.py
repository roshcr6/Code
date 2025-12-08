import math
choice = 0
while choice != 3:
    choice = int(input("\n1. Summation\n2. Factorial\n3. Exit\nEnter your choice: "))
    if choice == 1:
        num = int(input("Enter the number : "))
        summation = num * (num + 1) // 2
        print(f"Sum of first {num} natural numbers : {summation}")
    elif choice == 2:
        num = int(input("Enter the number : "))
        print(f"Factorial of {num} : {math.factorial(num)}")
    elif choice == 3:
        print("Exiting...")
    else:
        print("Invalid choice")
