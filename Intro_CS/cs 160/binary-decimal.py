num=input("enter binary number: ");
num=int(num);

total = 0
power = 0

while num > 0:
    total += (2**power) * (num%10);
    num = (num//10);
    power += 1
print (total)
