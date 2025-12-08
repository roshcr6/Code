x = 1
while x != 4:
    print("Choose")
    print("1. Area of Rectangle")
    print("2. Area of Square")
    print("3. Area of Triangle")
    print("4. Exit")

    x = int(input("Enter your choice: "))

    if x == 1:
        b = float(input("Base : "))
        h = float(input("Height : "))
        print(f"Area of Rectangle : {b*h}")

    elif x == 2:
        s = float(input("Side : "))
        print(f"Area of Square : {s*s}")

    elif x == 3:
        b = float(input("Base : "))
        h = float(input("Height : "))
        print(f"Area of Triangle : {0.5*b*h}")

    elif x == 4:
        print("Exiting...")

    else:
        print("Invalid input")
