password = input("Enter password: ")

upper = False
lower = False
digit = False
special = False

special_chars = "!@#$%^&*()_+-=[]{}|;:'\",.<>?/"

for ch in password:
    if ch.isupper():
        upper = True
    elif ch.islower():
        lower = True
    elif ch.isdigit():
        digit = True
    elif ch in special_chars:
        special = True

if len(password) >= 8 and upper and lower and digit and special:
    print("Strong Password")
else:
    print("Weak Password")
