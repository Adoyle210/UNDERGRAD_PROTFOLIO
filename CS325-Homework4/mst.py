#----------------------------------------------------------------------------
#Cs 325: Homework 4 
#Date: 02/21/2022
#By Alexis Doyle
#----------------------------------------------------------------------------

#node object for managing data in the tree
class node:
  x = 0
  y = 0


#----------------------------------------------------------------------------
#Function: mstWeight
#takes an array of nodes and compares distances to find findDis 
#--------------------------------------------------------------------------
def mstWeight(vertArray):

    distance = 0 #total distance starting at zero
    temp = node() #making a temp node 
    length = len(vertArray)
    for j in range(length - 1): #looping through array
        
        #setting up and getting the root of the tree
        if j == 0:
            root = vertArray[0] #comapring root to find the closest discance
            vertArray.pop(0)    #remove from list to be compared to       
            temp.distance = 100 #used for comparing 
       
        #setting up for other nodes
        else:
            root = temp
            vertArray.remove(temp) 
            temp.distance = 100   

        length = len(vertArray)
        #loop to start comparing 
        for i in range(length):
            next = vertArray[i]
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
        
        
    return distance

#----------------------------------------------------------------------------
#function: main
#this is the programs diver
#----------------------------------------------------------------------------
def main():
    with open("graph.txt", "r") as file: #oppening text file

        num = file.readline() #gets the num of test cases
        num = int(num) 

        for testNum in range (num): #loops for each test case 
            numVert = file.readline() #gets the num of verticies
            numVert = int(numVert)
            
            vertices = [] #array for verticies
            for i in range(numVert):  #loops to get all the verticies in an array

                temp = file.readline().split() #stores in array
                
                x = int(temp[0])
                y = int(temp[1])
            
                addNode = node()  #making node to be added
                addNode.x = x
                addNode.y = y

                vertices.append(addNode) # add it to array

            weight = mstWeight(vertices) #do current test

            #prining results like in solution
            print('Test case %d:' %(testNum +  1), "MST weight", weight)
            print()

            #continue loopp

#call to run the program 
main()
