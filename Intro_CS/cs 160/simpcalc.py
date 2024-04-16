def add(x,y):
    return  x + y 
    
def sub(x,y):
    return  x - y

def divide(x,y):
    return  x/y
    
def multiply(x,y):
   return x*y

def exponent(x,y):
     return x**y
     
def convert(x):
    result = []
    while x >= 0 :
     result.append(x%2);
     x = (x//2);
     if x == 0:
         result.reverse()
         return result


def calc():
    math=input("Enter 'yes' if you want to do a calcuation: ")
    if math.lower() == 'yes':
        print("Pick an operation ")
        print("1) Add")
        print("2) Subtract")
        print("3) Multiply")
        print("4) Divide")
        print("5) Exponent")
        print("6) Exit")
        math2 = input("operation: ")
        number =int(input("Enter a number: "))
        number2 = int(input("Enter second number: "))
        
        while number and number2 > 0:
            if math2 == '1' :
                print(number,"+",number2,"=", add(number,number2))
                print("In binary", convert(add(number,number2)))
                break
        
            elif math2 == '2' :
                print(number,"-",number2,"=", sub(number,number2))
                print("In binary", convert(sub(number,number2)))
                break
        
            elif math2 == '3' :
                print(number,"*",number2,"=", multiply(number,number2))
                print("In binary", convert(multiply(number,number2)))
                break
        
            elif math2 == '4' :
                print(number,"/",number2,"=", divide(number,number2))
                print("In binary", convert(divide(number,number2)))
                break

            elif math2 == '5' :
                print(number,"**",number2,"=", exponent(number,number2))
                print("In binary", convert(exponent(number,number2)))
                break

            else:
                exit()

        else:
            exit()


print (calc())


             

