{---------------------------------------------------------
- NAME: Alexis Doyle
- DATE: 16 FEB 2023
- HW4: SEMANTICS (part one)
---------------------------------------------------------}
module Stacklang1 where

-- defintion of the abstract syntax and type definition
type Prog = [Cmd]

data Cmd 
    = LD Int 
    | ADD
    | MULT
    | DUP
    deriving Show 

type Stack = [Int] 


-- runs with a stack ... if error return nothing 
run :: Prog -> Stack -> Maybe Stack  -- runs with a stack ... if error retunt nothing 
run [] x = Just x
run x s = runSub x (Just s)


semCmd :: Cmd -> Stack -> Maybe Stack
semCmd (LD x) s = Just(x:s)
semCmd (ADD) x = 
    if length x <= 1
        then Nothing
    else addCmd x
semCmd (MULT) x =
    if length x <= 1
        then Nothing
    else multCmd x 
semCmd (DUP) [] = Nothing
semCmd (DUP) (x:xs) = Just([x,x] ++ xs)
otherwise = Just([])

runSub :: Prog -> Maybe Stack -> Maybe Stack
runSub x Nothing = Nothing 
runSub [] (Just x) = Just x
runSub (x:xs) (Just s) = runSub xs (semCmd x s)

addCmd :: Stack -> Maybe Stack
addCmd (x:y:xs) = Just([x + y] ++ xs)

multCmd :: Stack -> Maybe Stack
multCmd (x:y:xs) = Just([x * y] ++ xs)

stack1 :: Stack
stack1 = [1, 2, 3, 4, 5]

test1 = [LD 3, DUP, ADD, DUP, MULT]
test2 = [LD 3, ADD]
test3 = []
test4 = [ADD, ADD, ADD, ADD]