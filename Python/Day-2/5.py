n = int(input("Enter an integer: "))
sum_ = 0
for i in range(1, n + 1):
    sum_ += i * i
print("Sum of squares from 1 to", n, "is:", sum_)
