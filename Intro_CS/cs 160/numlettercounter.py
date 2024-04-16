def names():
    name_list=[]
    name=" "
    while name != 'exit':
        name=input("Enter a name or exit: ")
        name_list.append(name.lower().strip())
    name_list.remove('exit')
    return(name_list)

def mainwords():
    name = names()
    letter=input("Enter letter you would like to check for: ")
    count = 0
    for i in range(len(name)):
        x = name[i]
        for i in  range (len(name[i])):
            if x[i] == letter:
                count += 1 
    print ("It repeats " + str(count) + " times")

def numbers():
    number_list=[]
    number=" "
    while number != 'exit':
        number=input("Enter a number or exit: ")
        try:
            number = int(number)
            number_list.append(number)
        
        except ValueError:
            if number == 'exit':
                print (number_list)
                return number_list
            else:
                number=input("Enter a number or exit: ")
    return number_list

def numssums(x,y): 
    num=0
    num1=0
    num2=len(x)
    num3=len(y)
    for i in range(len(x)):
        num += x[i]
    for i in range (len(y)):
        num1 += y[i]
    return (num, num1)
     
def numsavg(x,y,z,a):
    avg = x/z
    avg1 = y/a
    return (avg,avg1)

def numlen(x,y):
    if len(x) == len(y):
        return True
    else:
        return False

def numlisum(x,y):
    if x == y:
        return True
    else:
        return False

def numcom(x,y):
    listado = []
    for i in range(len(x)):
        a = x[i]
        a = int(a)
        for i in range(len(y)):
            if a == y[i]:
                listado.append(a)
    return (listado)
    
def mainnum():
    num = numbers()
    nums = numbers()
    num2 = len(num)
    num3 = len(nums)
    sum = numssums(num,nums)
    sum1 = sum[0]
    sum2 = sum[1]
    avg = numsavg(sum[0],sum[1],num2,num3)
    print("first list sum: " + str(sum[0]))
    print("first list average: " + str(avg[0]))
    print("second list sum: " + str(sum[1]))
    print("second list average: " + str(avg[1]))
    print("same length for list: " + str(numlen(num,nums)))
    print("same sum for list: " + str(numlisum(sum1,sum2)))
    print("common numbers the list have: " + str(numcom(num,nums)))
    
def chowmein():
    main=int(input("Do you want to make a list of 1) names 2) numbers: "))
    if main == 1:
        mainwords()
    elif main == 2:
        mainnum()
    else:
        chowmein()

chowmein()
