nums = input("Enter numbers separated by spaces: ")

num_list = []

for x in nums.split():
    num_list.append(int(x))

print("List:", num_list)
print("Sum:", sum(num_list))
