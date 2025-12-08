y= int(input("Year : "))
if y % 4 == 0:
        if y % 100 == 0:
                if y % 400 == 0:
                        print("Leap year") 
                else:
                    print("Not a leap year")  
        else:
            print("Leap year") 
else:
    print("Not a leap year")
