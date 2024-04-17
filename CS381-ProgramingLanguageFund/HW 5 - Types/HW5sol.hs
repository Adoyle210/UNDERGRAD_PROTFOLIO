-- Homework 5 (types)
-- Group 42
-- Alexis Doyle 
-- Saba Moallem 

module HW5sol where
import Data.Maybe

type Prog = [Cmd]
data Cmd = LDI Int 
		| ADD -- same as lang2 only int (old hw)
		| MULT -- same as lang2 only int (old hw)
		| DUP -- same as lang2 only (old hw)
		| DEC -- decrements the topmost element  (must be Int) on the stack 
		| SWAP -- xchanges the two topmost elements on the stack
		| POP Int -- pops k elements off the stack 
		| IFELSE Prog Prog -- same as lang2 only (old hw)
		| LDB Bool -- same as lang2 only (old hw)
		| LEQ -- same as lang2 only (old hw)
         deriving Show
		 

-- replacing Either from HW 4 to check types 		
data Val = I Int | B Bool 
		deriving Show

type Stack = [Val]
data Result = A Stack
		| RankError 
		| TypeError
          deriving Show
		  
type D = Stack -> Stack

-- following is used to rep operation ranks 
type Rank = Int
type CmdRank = (Int, Int)

----------------------------------------------------------------------
-- ADDED CODE BELOW ....

{------------------------------------------------------------
-- secondary function for either to check if it is an int or bool
-------------------------------------------------------------}
isInt :: Val -> Bool
isInt (B _) = False -- if bool flase
isInt (I _) = True -- if int true

{------------------------------------------------------------
-- secondary function returns bool from val
-------------------------------------------------------------}
isTF :: Val -> Bool
isTF (B x) = x  -- returns bool from Val

-- {------------------------------------------------------------
-- -- secondary function for run
-- -------------------------------------------------------------}
-- isNoth :: Maybe a -> Bool
-- isNoth (Just s) = False 
-- isNoth (Nothing) = True

{------------------------------------------------------------
-- secondary function for run 
-------------------------------------------------------------}
convertStack :: [Int] -> Stack
convertStack l = [(I i) | i <- l] -- converst int to stack

{------------------------------------------------------------
-- secondary function for run 
-------------------------------------------------------------}
convertIntList :: Maybe Stack -> [Int]
convertIntList (Nothing) = []
convertIntList (Just s) = [i | (I i) <- s]

{------------------------------------------------------------
-- secondary funtion that handles ADD
-------------------------------------------------------------}
addVal :: Val -> Val -> Val
addVal (I i) (I j) = I (i + j)

{------------------------------------------------------------
--  secondary function for LEQ
-------------------------------------------------------------}
compareVal :: Val -> Val -> Bool
compareVal (I i) (I j) = 
	if i <= j then True
	else False

{------------------------------------------------------------
-- secondary funtion that handles MULT
-------------------------------------------------------------}
multVal :: Val -> Val -> Val
multVal (I i) (I j) = I (i * j)

{------------------------------------------------------------
-- secondary function for swap
-------------------------------------------------------------}
valSwap :: Stack -> Maybe Stack
valSwap (x:y:s) = Just (y:x:s)

{------------------------------------------------------------
-- secondary function for POP 
-------------------------------------------------------------}
remove :: Stack -> Int -> Maybe Stack
remove [] _ = Just []
remove l 0 = Just l 
remove (_:ys) n = remove ys (n - 1)


{------------------------------------------------------------
-- takes stack command and returns maybe stack 
-------------------------------------------------------------}
semCmd :: Cmd -> Stack -> Maybe Stack
semCmd (LDI n) s = Just ((I n):s) -- loads ints
semCmd (LDB n) s = Just ((B n):s) -- loads bools
semCmd (ADD) s =
	if length s < 2 then Nothing -- two or more then nothing 
	else if isInt(head s) == False || isInt (head (tail s)) == False then Nothing -- Int check
	else Just ((addVal (head s) (head (tail s))):(tail (tail s)))
semCmd (MULT) s =
	if length s < 2 then Nothing -- two or more then nothing 
	else if isInt(head s) == False || isInt (head (tail s)) == False then Nothing -- Int check
	else Just ((multVal (head s) (head (tail s))):(tail (tail s))) 
semCmd (LEQ) s = 
	if length s < 2 then Nothing -- two or more then nothing 
	else if isInt(head s) == False || isInt (head (tail s)) == False then Nothing -- Int check
	else if compareVal (head s) (head (tail s)) == True then Just ((B True):(tail (tail s)))
	else Just ((B False):(tail (tail s)))
semCmd (DUP) [] = Nothing -- handling empty
semCmd (DUP) s = Just ((head s):s)
semCmd (IFELSE p1 p2) s = 
	if isInt(head s) == True then Nothing
	else if isTF(head s) == True then runIFELSE p1 (Just (tail s))
	else runIFELSE p2 (Just (tail s))
semCmd DEC [] = Nothing -- handling empty
semCmd DEC ((B x):s) = Nothing -- for bools
semCmd DEC ((I x):s) = Just((I (x - 1)):s) --for ints - 1
semCmd SWAP s = 
	if length s < 2 then Nothing
	else valSwap s
semCmd (POP k) s =
	if length s < k then Nothing 
	else if length s == k then Just []
	else remove s k 

{------------------------------------------------------------
-- Define a function rankC that maps each stack operation 
-- to its rank. 
-------------------------------------------------------------}
rankC:: Cmd -> CmdRank
rankC ADD = (2,1) -- remove two places one
rankC MULT = (2,1) -- remove two places one
rankC DEC = (1,1) -- remove one places one
rankC SWAP = (2,2) -- remove two places two
rankC (POP i) = (i,0) -- remove i places none
rankC DUP = (1,2) -- remove one places two
rankC LEQ = (2,1) -- remove two places one
rankC (LDI i) = (0,1) -- remove none places one
rankC (LDB b) = (0,1) -- remove none places one
rankC (IFELSE p1 p2) = (-1,-1) -- don't know what will be executed 

{------------------------------------------------------------
-- secondary function that handles branches of IFELSE
-------------------------------------------------------------}
rankIFELSE :: Prog -> Prog -> Maybe Rank -> Maybe Rank
rankIFELSE p1 p2 Nothing = Nothing
rankIFELSE p1 p2 (Just r) =
	if isNoth(rankP p1 (r - 1)) == True then Nothing
	else if isNoth(rankP p2 (r - 1)) == True then Nothing
	else if rank p1 (Just (r - 1)) < rank p2 (Just (r - 1)) then rank p1 (Just (r - 1))
	else rank p2 (Just (r - 1))

{------------------------------------------------------------
-- secondary function for rank
-------------------------------------------------------------}
rankTemp :: CmdRank -> Maybe Rank -> Maybe Rank
rankTemp (x,y) (Just r) = 
	if r < x then Nothing 
	else Just (r - x + y)

{------------------------------------------------------------
-- secondary function for rankP
-------------------------------------------------------------}
rank :: Prog -> Maybe Rank -> Maybe Rank
rank [] (Just r) = Just r
rank p Nothing = Nothing
rank ((IFELSE p1 p2):ps) (Just r) = rank ps (rankIFELSE p1 p2 (Just r))
rank (p:ps) (Just r) = rank ps (rankTemp (rankC p) (Just r))

{------------------------------------------------------------
-- Define a function rankP that computes the rank of a 
-- program when ran with a stack of rank r.
-------------------------------------------------------------}
rankP:: Prog -> Rank -> Maybe Rank
rankP [] r = Just r
rankP p r = rank p (Just r)

{------------------------------------------------------------
-- secondary function for run
-------------------------------------------------------------}
runR :: Prog -> Maybe Stack -> Maybe Stack
runR p Nothing = Nothing 
runR [] (Just s) = Just s 
runR (p:ps) (Just s) = runR ps (semCmd p s )

{------------------------------------------------------------
-- secondary function in semcmd for IFELSE
-------------------------------------------------------------}
runIFELSE :: Prog -> Maybe Stack -> Maybe Stack
runIFELSE [] s = s
runIFELSE p s = runR p s 

{------------------------------------------------------------
-- secondary function for run
-------------------------------------------------------------}
isNoth :: Maybe a -> Bool
isNoth (Just s) = False -- if maybe false
isNoth (Nothing) = True -- if nothing true

{------------------------------------------------------------
-- Define a function run for evaluating a program with a 
-- given stack 
-------------------------------------------------------------}
run :: Prog -> Stack -> Result
run p s = 
	if staticTF p (length s) == 0 then RankError
	else if isNoth (runR p (Just (convertStack s))) == True then TypeError
	else A (convertIntList (runR p (Just (convertStack s))))


	
{------------------------------------------------------------
-- secondary function to check stack rank 
-------------------------------------------------------------}
staticTF  :: Prog -> Rank -> Int 
staticTF  p r = 
	if rankP p r == Nothing then 0
	else 1
