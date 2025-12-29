t = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)

total = 0
product = 1

for num in t:
    total += num
    product *= num

print("Sum:", total)
print("Product:", product)

x = int(input("Enter number to search: "))

if x in t:
    print("Number is present")
else:
    print("Number is not present")

t = t + (11, 12)
print("Updated tuple:", t)
