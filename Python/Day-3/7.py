s = input("Enter a string: ")

vowels = "aeiouAEIOU"
v = 0
c = 0
sp = 0

for ch in s:
    if ch in vowels:
        v += 1
    elif ch.isalpha():
        c += 1
    elif ch == " ":
        sp += 1

print("Vowels:", v)
print("Consonants:", c)
print("Spaces:", sp)
