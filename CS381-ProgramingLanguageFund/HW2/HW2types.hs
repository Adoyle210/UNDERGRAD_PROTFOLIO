{---------------------------------------------------------------------
- CS 381: HomeWork 2
- Due: 01/25/2022
- By: Alexis Doyle
----------------------------------------------------------------------}
-- i couldn't get the line under to work i would get error: parse error on input `module'
--import HW2types
module HW2types where

import Data.List (nub,sort)


-- Types for Exercise 1
--
type Bag a = [(a,Int)]
nullList  = []
list = [2,3,3,5,7,7,7,8] {-this was an example in the exercise for testing-}
bag1 :: Bag Int
bag2 :: Bag Int
bag1 = [(5,1),(7,3),(2,1),(3,2),(8,1)]
bag2 = [(5,1),(8,6),(1,0),(3,7),(4,1)]

-- the following are functions that are to be defined for the exercise: 
{-PART A:-}
ins :: Eq a  => a -> Bag a -> Bag a
ins x []     = [(x,1)]
ins x (y:ys)  | x == fst y = (x,succ(snd y)):ys    {-this is like if and else -}
              | otherwise  = y : (ins x ys)

{-PART B:-}
del :: Eq a  => a -> Bag a -> Bag a
del a []     = []
del a (x:xs) | a == fst x = filter (\y -> (snd y) > 0) ((a,pred(snd x)):xs)
             | otherwise  = x : (del a xs)

{-PART C:-}
bag :: Eq a => [a] -> Bag a
bag []     = []
bag (x:xs) = ins x (bag xs)

{-PART D:-}            
subbag :: Eq a => Bag a -> Bag a -> Bool
subbag xs [] = False
subbag [] ys = True
subbag (x:xs) ys = check x ys && subbag xs ys

check x []     = False
check x (y:ys) | x == y = True
               | otherwise = check x ys

{-PART E:-}  
isSet :: Eq a => Bag a  -> Bag a -> Bag a
isSet [] ys     = []
isSet (x:xs) ys | check x ys = x : isSet xs ys
                | otherwise  = isSet xs ys

{-PART F:-} 
size :: Bag a -> Int
size [] = 0
size (x:xs) = snd x + size xs


-- Types and functions for Exercise 2
--
type Node  = Int
type Edge  = (Node,Node)
type Graph = [Edge]
type Path  = [Node]

{-from homework for testing-}
g :: Graph
g = [(1,2), (1,3), (2,3), (2,4), (3,4)]

h :: Graph
h = [(1,2), (1,3), (2,1), (3,2), (4,4)]

norm :: Ord a => [a] -> [a]
norm = sort . nub

-- the following are functions that are to be defined for the exercise: 
{-PART A:-}                  
nodes :: Graph -> [Node]
nodes [] = []
nodes (x:xs) = norm ([fst x, snd x] ++ nodes xs)

{-PART B:-}
suc :: Node -> Graph -> [Node]
suc x [] = []
suc x ((y1,y2):ys) | x == y1  = [y2] ++ suc x ys
                   | otherwise  = suc x ys

{-PART C:-}
detach :: Node -> Graph -> Graph
detach x [] = []
detach x ((y1,y2):ys) | x == y1 = detach x ys
                      | x == y2   = detach x ys
                      | otherwise = (y1,y2) : detach x ys

{-PART D:-}
bc :: Int -> Graph 
bc 1 = []
bc x = (bc (x-1) ++ [(x-1, x)])

cyc x = bc x ++ [(x,1)]

{-----------------------------------------------
Testing for exersise 2: 
*HW2types> nodes g
[1,2,3,4]

*HW2types> nodes [(1,8), (2,17)]
[1,2,8,17]

*HW2types> suc 1 [(1,5), (2,17), (3,15)]
[5]

*HW2types> suc 2 [(1,5), (2,17), (3,15)]
[17]

*HW2types> detach 2 [(1,5), (2,17), (3,15)]
[(1,5),(3,15)]

*HW2types> detach 1 [(1,1), (1,5), (1,9), (3,25), (1,29)]
[(3,25)]

*HW2types> cyc 1
[(1,1)]

*HW2types> cyc 2
[(1,2),(2,1)]

*HW2types> cyc 3
[(1,2),(2,3),(3,1)]

*HW2types> cyc 4
[(1,2),(2,3),(3,4),(4,1)]

-----------------------------------------------}

-- Types for Exercise 3
--
type Number = Int

type Point = (Number,Number)
type Length = Number

data Shape = Pt Point
           | Circle Point Length
           | Rect Point Length Length
           deriving Show

type Figure = [Shape]

type BBox = (Point,Point)

point = Pt (1,1)
circle = Circle (2,2) 2
rectangle = Rect (3,3) 3 3
f = [Pt (4,4), Circle (5,5) 3, Rect (3,3) 7 2]

-- the following are functions that are to be defined for the exercise: 
{-PART A:-}
width :: Shape -> Length
width (Pt p)          = 0
width (Circle p l)    = l*2
width (Rect p l1 l2)  = l1

{-PART B:-}
bbox :: Shape -> BBox
bbox (Pt p)           = (p, p)
bbox (Circle p l)     = ((fst p - l, snd p - l),((fst p + l),(snd p + l)))
bbox (Rect p l1 l2)   = (p, ((fst p + l1),(snd p + l2)))

{-PART C:-}
minX :: Shape -> Number
minX (Pt p) = fst p
minX (Rect p l1 l2) = fst p
minX (Circle p l) = fst p - l

{-PART D:-}
move :: Shape -> Point -> Shape
move (Pt p) v = (Pt (addPt p v))
move (Rect p l1 l2) v = (Rect (addPt p v) l1 l2)
move (Circle p l) v  = (Circle (addPt p v) l)

addPt :: Point -> Point -> Point
addPt (x1,y1) (x2,y2) = (x1+x2,y1+y2)

{-----------------------------------------------
Testing for exercise 3:
*HW2types> map width [Pt (4,4), Circle (5,5) 3, Rect (3,3) 7 2]
[0,6,7]

*HW2types> map bbox [Pt (4,4), Circle (5,5) 3, Rect (3,3) 7 2]
[((4,4),(4,4)),((2,2),(8,8)),((3,3),(10,5))]

*HW2types> map minX [Pt (4,4), Circle (5,5) 3, Rect (3,3) 7 2]
[4,2,3]

*HW2types> move (f!!1) (1,2)
Circle (6,7) 3

*HW2types> move (f!!0) (1,2)
Pt (5,6)

*HW2types> move (f!!2) (1,2)
Rect (4,5) 7 2
-----------------------------------------------}