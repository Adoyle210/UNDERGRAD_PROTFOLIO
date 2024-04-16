def summations(): 
    a = int(input("Enter starting point for X: "))
    b = int(input("Enter ending point for x: "))
    formula = int(input("would you like formula 1) f1(x)=10x^2 2) f2(x)= 2x^2 - 5 3) f3(x)=x+20 : "))
    sum=0
    for x in range(a,b+1):
        if formula==1: 
            form = (x**2)*10
        elif formula==2:
            form = (2*(x**2))-5
        elif formula==3:
            form = x+20
        sum+=form
        print(sum)  
    print("The summation is equal to " + str(sum) + ".")
    
def intergrations():
    a = int(input("Enter starting point for X: "))
    b = int(input("Enter ending point for x: "))
    n = int(input("Enter the number of shapes: "))
    width = (b-a)/n
    tor = int(input("would you like 1) rectangle 2) trapizoid: "))
    if tor==1: 
        formula = int(input("would you like formula 1) f1(x)=10x^2 2) f2(x)= 2x^2 - 5 3) f3(x)=x+20 : "))
        for x in range(a,b+1):
            if formula==1:
                form = (x**2)*10
                height=(form*width)
                area = width *height
            elif formula==2:
                form = (2*(x**2))-5    
                height=(form*width)
                area = width *height
            elif formula==3:
                form = x+20
                height=(form*width)
                area = width *height
            print(int(area))
        print("The integration for a rectangle is " + str(area) + ".")

    elif tor==2:
        formula = int(input("would you like formula 1) f1(x)=10x^2 2) f2(x)= 2x^2 - 5 3) f3(x)=x+20 : "))
        for x in range(a,b+1):
            if formula==1:
                form = (x**2)*10
                height=(form+(form+width)/2)
                area = width *height  
            if formula==2:
                form = (2*(x**2))-5
                height=(form+(form+width)/2)
                area = width *height    
            if formula==3:     
                form = x+20
                height=(form+(form+width)/2)
                area = width *height
            print(int(area))   
        print("The integration for a trapizoid is " + str(area) + ".")

def cal():
    calc = int(input("Would you like preform 1) summation or 2) intergration: "))
    if calc == 1:
        summations() 
    elif calc == 2:
        intergrations()
    pina=int(input("input 1) to make another calcuation 2) exit: "))
    if pina == 1:
        cal()
                 
cal()