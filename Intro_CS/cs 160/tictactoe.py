from random import randint
import time 

def players2():
    board = [['_' for _ in range(3)]for _ in range(3)]  
    isx = True 
    gameover = False
    while not gameover:
        printboard(board) 
        try:
            select=convertmove(selectspot())
            placepiece(select, isx ,board)    
        except ValueError:
            print("please pick a number 1-9 that is unoccupied.")
            continue
        gameover = winner(board) or draw(board)
        isx = not isx

def player1x():
    board = [['_' for _ in range(3)]for _ in range(3)] 
    printboard(board)
    print(" ")
    gameover = False
    while not gameover:
        try:
            selectspotcpu(board)
        except ValueError:
            print("please pick a number 1-9 that is unoccupied.")
            continue
        gameover = winner(board) or draw(board)

def player1o():
    board = [['_' for _ in range(3)]for _ in range(3)] 
    printboard(board)
    print(" ")
    gameover = False
    while not gameover:
        try:
            selectspotcpo(board)
        except ValueError:
            print("please pick a number 1-9 that is unoccupied.")
            continue
        gameover = winner(board) or draw(board)
        

def convertmove(select):
    select -= 1
    return(select // 3, select % 3)

def draw(board):
    for row in board:
        for val in row:
            if val == "_":
                return False
    printboard(board)
    print("It is a draw, no more moves")
    return True

def winner(board):
    win = None
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] and board[i][0] != "_":
            win = board[i][0]
            break
        if board[0][i] == board[1][i] == board[2][i] and board[0][i] != "_":
            win = board[0][i]
            break
        if board[1][1] != "_" :
            if (board[0][0] == board[1][1] == board [2][2] or board[0][2] == board[1][1] == board[2][0]):
                win == board[1][1]
    if win != None: 
        print(" ")
        printboard(board)
        print(f"{win} is the winner!")
        return True
    return False

def placepiece(select, isx, board):
    i, j = select
    if board[i][j] == "_":
        board[i][j] = "X" if isx else "O"
    else: 
        raise ValueError

def printboard(board):
    for row in board:
        print(row)

def selectspot():
    select=int(input("select a spot: "))
    if  not 1 <= select <= 9:
        raise ValueError  
    return select

def selectspotcpu(board):
    player = 0
    cpu = 1
    while cpu > player:
        select=int(input("select a spot: "))
        player += 1
        if  not 1 <= select <= 9:
            raise ValueError 
        else:
            select -= 1
            i = select // 3
            j = select % 3
        if board[i][j] == "_":
            board[i][j] = "X" 
            printboard(board)
        else: 
            raise ValueError
    while cpu == player: 
        time.sleep(1)
        print(" ")
        selectcpu=randint(0, 8)
        cpu += 1
        i = selectcpu // 3
        j = selectcpu % 3
        if board[i][j] == "_":
            board[i][j] = "O" 
            printboard(board)
       
def selectspotcpo(board):
    player = 0
    cpu = 1
    while cpu > player:
        select=int(input("select a spot: "))
        player += 1
        if  not 1 <= select <= 9:
            raise ValueError 
        else:
            select -= 1
            i = select // 3
            j = select % 3
        if board[i][j] == "_":
            board[i][j] = "O" 
            printboard(board)
        else: 
            raise ValueError
    while cpu == player: 
        time.sleep(1)
        print(" ")
        selectcpu=randint(0, 8)
        cpu += 1
        i = selectcpu // 3
        j = selectcpu % 3
        if board[i][j] == "_":
            board[i][j] = "X" 
            printboard(board)     
            
def Chowmein():
    print("instructions: pick numbers displayed on the following board to select a spot")
    print(" ")
    time.sleep(1)
    print("[1, 2, 3]")
    print("[4, 5, 6]")
    print("[7, 8, 9]")
    time.sleep(4)
    print(" ")
    playernum=(input("would you like one or two players: "))
    if playernum.lower() ==  'two':
        print("X goes first")
        players2()
    elif playernum.lower() == 'one':
        piece=input("would you like 'x' or 'o': ")
        if piece.lower() == 'x':
            player1x()
        elif piece.lower() == 'o':
            player1o()
        else:
            print("error that is not an option, try again")
            Chowmein()
    else:
        print("please write out one or two, try again")
        Chowmein()
    
Chowmein()

