s = input("Enter a string: ")

print("Length:", len(s))
print("Uppercase:", s.upper())
print("Lowercase:", s.lower())

if s == s[::-1]:
    print("Palindrome")
else:
    print("Not Palindrome")

vowels = "aeiouAEIOU"
new_string = ""
vowel_count = 0

for ch in s:
    if ch in vowels:
        new_string += "_"
        vowel_count += 1
    else:
        new_string += ch

print("After replacing vowels:", new_string)
print("Number of vowels:", vowel_count)
