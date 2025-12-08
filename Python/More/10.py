choice = 0

while choice != 3:
    print("\n1. Check Prime Number\n2. Check Armstrong Number\n3. Exit")

    choice = int(input("Enter your choice: "))

    if choice == 3:
        print("Exiting...")
        break

    num = int(input("Enter the number: "))

    if choice == 1:
        if num <= 1:
            print(f"{num} is NOT a prime number")
        else:
            prime = True
            for i in range(2, int(num**0.5) + 1):
                if num % i == 0:
                    prime = False
                    break
            if prime:
                print(f"{num} is a Prime Number")
            else:
                print(f"{num} is NOT a Prime Number")

    elif choice == 2:
        temp = num
        num_digits = 0
        if temp == 0:
            num_digits = 1
        else:
            while temp > 0:
                temp //= 10
                num_digits += 1

        temp = num
        sum_of_powers = 0
        while temp > 0:
            digit = temp % 10
            sum_of_powers += digit ** num_digits
            temp //= 10

        if sum_of_powers == num:
            print(f"{num} is an Armstrong Number")
        else:
            print(f"{num} is NOT an Armstrong Number")

    else:
        print("Invalid choice")
