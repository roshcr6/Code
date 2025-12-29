import random

numbers = []

for i in range(10):
    numbers.append(random.randint(1, 100))

print("List:", numbers)
print("Maximum:", max(numbers))
print("Minimum:", min(numbers))
print("Average:", sum(numbers) / len(numbers))

numbers.reverse()
print("Reversed list:", numbers)

even_squares = []

for num in numbers:
    if num % 2 == 0:
        even_squares.append(num * num)

print("Squares of even numbers:", even_squares)
