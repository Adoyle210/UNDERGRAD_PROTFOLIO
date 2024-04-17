{-----------------------------------------------------------------------
    Class: CS 381
    Assignment: Homework 5
    Date: 02/17/2022
    Authors: Alexis Doyle, YuWei Koh, Arman Askari 
------------------------------------------------------------------------}
module StackTypes where


type Prog = [Cmd]


data Cmd = LDI Int
         |LDB Bool -- loads a bool onto the stack
         |LEQ      --removes top int and second int. if top <= second then push true else push false 
         | ADD
         | MULT
         | DUP
         |IFELSE Prog Prog -- if val on top is true run first else run second prog TYPEMODULE HAS EXAMPLE FOR THIS PART
         | INC
         | DEC     -- decrements the top most element (must be int)
         | SWAP    -- excahnges the two topmost elements 
         | POP Int -- pops k element from the stack
         deriving(Eq,Show)

-- can use this instead of either like in hw 4
data Val = I Int 
          | B Bool  
   

type Stack = [Val]

type Rank = Int

type CmdRank = (Int,Int)


prog :: Prog -> Stack -> Maybe Stack
prog []     s = Just s
prog (c:cs) s = cmd c s >>= prog cs


cmd :: Cmd -> Stack -> Maybe Stack
cmd (LDI n)s            = Just (I n:s)
cmd (LDB b)s            = Just (B b:s)
--cmd LEQ (I n: I k:s) < >
cmd ADD (I n: I k:s)    = Just (I (n+k):s)
cmd MULT (I n: I k:s)   = Just (I(n*k):s)
cmd DUP (n:s)           = Just (n:n:s)
--cmd IFELSE Prog Prog
cmd DEC (I n: s)        = Just(I (n - 1):s)
cmd INC (I n: s)        = Just (I (n + 1):s)
cmd SWAP (n:k:s)        = Just (k:n:s)
cmd (POP  k) s          = Just (drop k s)
cmd _        _          = Nothing



--NEED TO ADD RANKS ... just need IFELSE now :)
rankC :: Cmd -> CmdRank
rankC (LDI _)  = (0,1)
rankC (LDB _)  = (0,1)
rankC (LEQ)    = (2,1)
rankC (ADD)    = (2,1)
rankC (MULT)   = (2,1)
rankC (DUP)    = (1,2)
--rankC (IFELSE _ _) 
rankC (INC)    = (1,1)
rankC (SWAP)   = (2,2)
rankC (DEC)    = (1,1) 
rankC (POP x)  = (x,0)


rankP :: Prog -> Rank -> Maybe Rank
rankP [] x = Just x
rankP cmds x = rank cmds x

rank :: Prog -> Rank -> Maybe Rank  --auxiliary function 
rank [] x = Just x
rank (x:xs) r = let (popsnum,pushsnum) = rankC x in
                    if (popsnum < r) then rank xs (r - popsnum + pushsnum)
                    else Nothing

{-Example from TypeCheck.hs: 
evalStatTC :: Expr -> Maybe Val
evalStatTC e | typeCorrect e = Just (eval e)
             | otherwise     = Nothing
-}

-- this function needs check rank and if the rank is good then run and call Cmd otherwise print rank error if therre is a stack underflow then print type error
semStatTC :: Prog -> Stack -> Maybe Stack
semStatTC prg stk = if (rankP prg (length stk)) == Nothing then Nothing
                    else prog prg stk

semStatTC' :: Prog -> Maybe Stack
semStatTC' prg = if (rankP prg 0) == Nothing then Nothing
                    else (prog prg [])


type PrgStk = Prog -> Stack -> Maybe Stack

prog' :: PrgStk
prog' []     s = Just s
prog' (c:cs) s = cmd c s >>= prog' cs