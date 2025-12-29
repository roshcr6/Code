#Write a program to implement a simple calculator and perform all arithmetic operations

while True:
    print("\n--- Simple Calculator ---")
    print("1. Addition (+)")
    print("2. Subtraction (-)")
    print("3. Multiplication (*)")
    print("4. Division (/)")
    print("5. Power (**)")
    print("6. Floor Division (//)")
    print("7. Exit")
    choice = int(input("Enter your choice (1-7): "))
    if choice == 7:
        print("Calculator Closed")
        break
    num1 = float(input("Enter first number: "))
    num2 = float(input("Enter second number: "))
    if choice == 1:
        print("Result:", num1 + num2)
    elif choice == 2:
        print("Result:", num1 - num2)
    elif choice == 3:
        print("Result:", num1 * num2)
    elif choice == 4:
        if num2 != 0:
            print("Result:", num1 / num2)
        else:
            print("Error: Division by zero")
    elif choice == 5:
        print("Result:", num1 ** num2)
    elif choice == 6:
        if num2 != 0:
            print("Result:", num1 // num2)
        else:
            print("Error: Division by zero")
    else:
        print("Invalid choice")
