#----------------------------------------------------------------------------------------------------------------------
#   CS 325: Homework 6
#   Date: March 12, 2022
#   Author: Alexis Doyle
#   Description:
#   Sources/refrences: https://docs.python.org/3/library/fileinput.html 
#   https://stackoverflow.com/questions/7033987/get-a-file-from-cli-input
#----------------------------------------------------------------------------------------------------------------------
import sys  #this is for reading the file from the command line
import datetime

#----------------------------------------------------------------------------
# class: city
# for storeing all the places the saleman is gonna travel
#--------------------------------------------------------------------------
class city:
  id = 0
  x = 0
  y = 0

#----------------------------------------------------------------------------
#Function: tsp
# implementation of traveling Salesman Problem
#takes an array of nodes and compares distances to find findDis 
#--------------------------------------------------------------------------
def tsp(tsp, filename):
    output = filename + ".tour"
    with open(output, 'w') as file: 
        distance = 0 #total distance starting at zero
        temp = city() #making a temp node 
        length = len(tsp)
        tspPath = []
        for j in range(length - 1): #looping through array    
            #setting up and getting the root of the tree
            if j == 0:
                root = tsp[0] #comapring root to find the closest discance
                tspPath.append(root)
                tsp.pop(0)    #remove from list to be compared to       
                temp.distance = 10000000000 #used for comparing 
        
            #setting up for other nodes
            else:
                root = temp
                tsp.remove(temp) 
                temp.distance =  10000000000

            length = len(tsp)
            #loop to start comparing 
            for i in range(length):
                next = tsp[i]
                # finds the distance using a^2 + b^2 = c^2:
                #finding a and b sq
                a = pow((root.x - next.x), 2) 
                b = pow((root.y - next.y), 2)
                #getting c sq to find c 
                c = a + b
                dis = pow(c, 1/2)
                dis = round(dis)
                #c = findDis(root.x, root.y, next.x, next.y)
                next.distance = dis 
            
                if next.distance <= temp.distance: #updates temp if found closer choice 
                    temp = next

            distance += temp.distance
            tspPath.append(temp)

        #calcuating and adding returning distance to start
        start = tspPath[0]
        end =  tspPath[len(tspPath) - 1]

        a = pow((start.x - end.x), 2) 
        b = pow((start.y - end.y), 2)
        
        c = a + b
        returnDis = pow(c, 1/2)
        returnDis = round(returnDis)
        distance += returnDis
        
        #printing output:   
        print(distance, file=file)
        for x in range(len(tspPath)):
            print(tspPath[x].id, file=file)
      



#----------------------------------------------------------------------------
#function: main
#this is the programs diver
#----------------------------------------------------------------------------
if __name__ == "__main__":
    start = datetime.datetime.now() #start of program so start of time
  
    filename = sys.argv[-1]
    with open(filename, "r") as file: #oppening text file
        num = file.readline() #gets num of cities 
        num = int(num) 

        graph = []
        for i in range (num): #loop to fill the graph
            temp = file.readline().split() #stores in array

            addcity = city()
            addcity.id = (int(temp[0]))#city identifier 
            addcity.x = (int(temp[1]))#x coordinate
            addcity.y = (int(temp[2]))#y coordinate 
            
            graph.append(addcity) # putting array in graph

        tsp(graph, filename)
        end = datetime.datetime.now() # "end" of program so end time
        totalTime = end - start
        print("Time take: ", totalTime, "seconds")
            


