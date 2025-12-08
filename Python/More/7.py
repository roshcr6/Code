choice = 0

while choice != 4:
    print("\n1. Sum of digits")
    print("2. Reverse the number")
    print("3. Check palindrome")
    print("4. Exit")

    choice = int(input("Enter your choice: "))
    num = int(input("Enter the number: "))

    if choice == 1:
        s = 0
        temp = num
        while temp != 0:
            s += temp % 10
            temp //= 10
        print(f"Sum of digits of {num} : {s}")

    elif choice == 2:
        rev = 0
        temp = num
        while temp != 0:
            rev = rev * 10 + (temp % 10)
            temp //= 10
        print(f"Reverse of {num} : {rev}")

    elif choice == 3:
        rev = 0
        temp = num
        while temp != 0:
            rev = rev * 10 + (temp % 10)
            temp //= 10

        if rev == num:
            print(f"{num} is a Palindrome")
        else:
            print(f"{num} is NOT a Palindrome")

    elif choice == 4:
        print("Exiting...")

    else:
        print("Invalid choice")
