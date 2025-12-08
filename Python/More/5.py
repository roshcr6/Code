print("Category : ")
print("Deluxe Car -> D")
print("Semi Deluxe Car -> S")
print("Ordinary Car -> O")

category = input("Enter category code (D/S/O): ").upper()
days = int(input("Number of days : "))

if category == "D":
    rate = 1000
elif category == "S":
    rate = 800
elif category == "O":
    rate = 700
else:
    print("Invalid category code!")
    exit()

amount = rate * days
service_tax = amount * 0.09
total_payable = amount + service_tax

print("\n----- CAB BILL SUMMARY -----")
print(f"Car Category      : {category}")
print(f"Number of Days    : {days}")
print(f"Base Amount       : ₹{amount}")
print(f"Service Tax (9%)  : ₹{service_tax}")
print(f"Total Payable     : ₹{total_payable}")
