price = float(input("Enter price of the item: "))
quantity = int(input("Enter quantity purchased: "))

total_amount = price * quantity

if total_amount <= 25000:
    discount_rate = 0.05      
elif total_amount <= 50000:
    discount_rate = 0.10      
else:
    discount_rate = 0.20      

discount_amount = total_amount * discount_rate
net_amount = total_amount - discount_amount

print("\n----- BILL SUMMARY -----")
print(f"Total Amount      : {total_amount}")
print(f"Discount Amount   : {discount_amount}")
print(f"Net Amount        : {net_amount}")
