{---------------------------------------------------------
- NAME: Alexis Doyle
- DATE: 16 FEB 2023
- HW4: SEMANTICS (part two)
---------------------------------------------------------}
module Stacklang2 where 

type Prog = [Cmd]
type Stack = [Either Bool Int]

data Cmd
    = LDI Int
    | LDB Bool
    | LEQ
    | ADD
    | MULT
    | DUP
    | IFELSE Prog Prog

    deriving Show

-- runs with a stack ... if error return nothing 
run :: Prog -> Stack -> Maybe Stack  -- runs with a stack ... if error retunt nothing 
run [] x = Just x
run x s = runSub x (Just s)

semCmd :: Cmd -> Stack -> Maybe Stack
semCmd (LDI x) s = Just((Right x):s) -- loads ints
semCmd (LDB x) s = Just((Left x):s) -- loads bools
semCmd (ADD) s = -- for ADD
    if length s <= 1 
        then Nothing
    else (addR s)  -- else calls second function
semCmd (MULT) s =
    if length s <= 1
        then Nothing
    else (multR s)
semCmd (LEQ) s = 
    if length s <= 1
        then Nothing
    else (leqR s)
semCmd (DUP) [] = Nothing
semCmd (DUP) (x:xs) = Just([x,x] ++ xs)
semCmd (IFELSE x1 x2) s =
    if head s == Left True
        then run x1 (tail s)
    else if head s == Left False
        then run x2 (tail s)
    else Nothing

addR :: Stack -> Maybe Stack 
addR (x:y:xs) =
    if checkInt x == False || checkInt y == False
        then Nothing
    else Just((addCmd x y) :xs)

multR :: Stack -> Maybe Stack
multR (x:y:xs) =
    if checkInt x == False || checkInt y == False 
        then Nothing
    else Just((multCmd x y) :xs)

leqR :: Stack -> Maybe Stack
leqR (x:y:xs) = 
    if checkInt x == False || checkInt y == False
        then Nothing
    else if x <= y then Just((Left True) :xs)
    else Just((Left False) :xs)

addCmd :: Either Bool Int -> Either Bool Int -> Either Bool Int
addCmd (Right x) (Right y) = Right(x + y)

multCmd :: Either Bool Int -> Either Bool Int -> Either Bool Int
multCmd (Right x) (Right y) = Right(x * y)

checkInt :: Either Bool Int -> Bool 
checkInt (Right _ ) = True 
checkInt (Left _ ) = False

runSub :: Prog -> Maybe Stack -> Maybe Stack
runSub x Nothing = Nothing 
runSub [] (Just x) = Just x
runSub (x:xs) (Just s) = runSub xs (semCmd x s)

stack1 :: Stack
stack1 = [Right 1, Right 3, Right 5, Right 7, Right 9]

stack2 :: Stack
stack2 = [Left True, Right 3]

test1 = [LDI 3, DUP, ADD, DUP, MULT]
test2 = [LDB True, DUP, IFELSE [LDI 1][LDI 0]]
test3 = [LEQ]
test4 = [ADD, ADD, MULT, DUP]
test5 = [LEQ, IFELSE [] [], LDI 9]
test6 = [LDI 5, LDI 2, LEQ, IFELSE [LDI 10, DUP] [], ADD]
test7 = [LDI 5, LDI 7, LEQ, IFELSE [LDI 10, DUP] [LDI 20, DUP], ADD]
test8 = [LDI 1, LDI 2, LDI 3, LDI 4, LDI 5, ADD, ADD, ADD, ADD]