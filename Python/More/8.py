choice = 0

while choice != 3:
    print("\n1. Find divisors\n2. Check perfect number\n3. Exit")

    choice = int(input("Enter your choice: "))
    

    if choice == 1:
        num = int(input("Enter the number: "))
        print(f"Divisors of {num}: ")
        for i in range(1, num + 1):
            if num % i == 0:
                print(i)

    elif choice == 2:
        num = int(input("Enter the number: "))
        s = 0
        for i in range(1, num):
            if num % i == 0:
                s += i

        if s == num:
            print(f"{num} is a Perfect Number")
        else:
            print(f"{num} is NOT a Perfect Number")

    elif choice == 3:
        print("Exiting...")

    else:
        print("Invalid choice")
