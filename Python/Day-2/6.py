a = float(input("Enter coefficient a: "))
b = float(input("Enter coefficient b: "))
c = float(input("Enter coefficient c: "))
d = b*b - 4*a*c   
if d > 0:
    root1 = (-b + d**0.5) / (2*a)
    root2 = (-b - d**0.5) / (2*a)
    print("Roots are real and different:")
    print("Root 1:", root1)
    print("Root 2:", root2)
elif d == 0:
    root = -b / (2*a)
    print("Roots are real and same:")
    print("Root:", root)
else:
    real_part = -b / (2*a)
    imag_part = (-d)**0.5 / (2*a)
    print("Roots are complex:")
    print(f"Root 1:{real_part:.2f}+{imag_part:.2f}i")
    print(f"Root 2:{real_part:.2f}-{imag_part:.2f}i")
