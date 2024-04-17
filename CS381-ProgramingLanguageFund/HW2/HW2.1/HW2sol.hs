{-------------------------------------------------------------------------------------------
- CS 381: HOMEWORK 2 
- Due: 1/30/2023
- By: Alexis Doyle
--------------------------------------------------------------------------------------------}
module HW2sol where
import HW2types
import Data.List
sname = "Alexis Doyle"


nlist = [] {- this is a null list -}

list = [2,3,3,5,7,7,7,8] {- this is an example given in the hw -}

bag1 :: Bag Int
bag1 = [(5,1),(7,3),(2,1),(3,2),(8,1)]

bag2 :: Bag Int
bag2 = [(5,1),(8,6),(1,0),(3,7),(4,1)]


{--------------------------------------------------------------------------------------------
- EX1: PART A 
- Define the function ins that inserts an element into a multiset.
--------------------------------------------------------------------------------------------}
ins :: Eq a  => a -> Bag a -> Bag a
ins x []     = [(x,1)]
ins x (y:ys)  | x == fst y = (x,succ(snd y)):ys    {- this is like if and else -}
              | otherwise  = y : (ins x ys)

{---------------------------------------------------------------------------------------------
- EX1: PART B 
- Define the functiondel that removes a single element froma multiset. 
- Note that deleting 3 from {2,3,3,4} yields {2,3,4} where as deleting 3 from {2,3,4} yields {2,4}.
---------------------------------------------------------------------------------------------}
del :: Eq a  => a -> Bag a -> Bag a
del a []     = []
del a (x:xs) | a == fst x = filter (\y -> (snd y) > 0) ((a,pred(snd x)):xs)
             | otherwise  = x : (del a xs)

{---------------------------------------------------------------------------------------------
-  EX1: PART C 
- Define a function bag that takes a list of values and produces a multiset representation.
---------------------------------------------------------------------------------------------}
bag :: Eq a => [a] -> Bag a
bag []     = []
bag (x:xs) = ins x (bag xs)

{---------------------------------------------------------------------------------------------
-  EX1: PART D 
- Define a function subbag that determines whether or not its first argument bag is contained in the second.
---------------------------------------------------------------------------------------------}            
subbag :: Eq a => Bag a -> Bag a -> Bool
subbag xs [] = False
subbag [] ys = True
subbag (x:xs) ys = check x ys && subbag xs ys

check x []     = False
check x (y:ys) | x == y = True
               | otherwise = check x ys

{---------------------------------------------------------------------------------------------
-  EX 1: PART E 
-  Define a function isSet that tests whether a bag is actually a set, which is the case when 
- each element occurs only once.
---------------------------------------------------------------------------------------------}  
isSet :: Eq a => Bag a  -> Bag a -> Bag a
isSet [] ys     = []
isSet (x:xs) ys | check x ys = x : isSet xs ys
                | otherwise  = isSet xs ys

{---------------------------------------------------------------------------------------------
-  EX 1: PART F
- Define a function size that computes the number of elements contained in a bag.
---------------------------------------------------------------------------------------------} 
size :: Bag a -> Int
size [] = 0
size (x:xs) = snd x + size xs

{- added graphs from excersice -}
g :: Graph
g = [(1,2), (1,3), (2,3), (2,4), (3,4)]

h :: Graph
h = [(1,2), (1,3), (2,1), (3,2), (4,4)]

{--------------------------------------------------------------------------------------------
- EX2: PART A 
- Define the function nodes :: Graph -> [Node] that computes the list of nodes contained in a given graph.
- For example, nodes g = [1,2,3,4].
--------------------------------------------------------------------------------------------}
nodes :: Graph -> [Node]
nodes [] = []
nodes (x:xs) = norm ([fst x, snd x] ++ nodes xs)

{--------------------------------------------------------------------------------------------
- EX2: PART B
- Define the function suc :: Node -> Graph -> [Node] that computes the list of successors for a node in a given graph. 
- For example, suc 2 g = [3,4], suc 4 g = [],and suc 4 h = [4].
--------------------------------------------------------------------------------------------}
suc :: Node -> Graph -> [Node]
suc x [] = []
suc x ((y1,y2):ys) | x == y1  = [y2] ++ suc x ys
                   | otherwise  = suc x ys

{--------------------------------------------------------------------------------------------
- EX2: PART C
-  Define the function detach :: Node -> Graph -> Graph that removes a node together with all 
- of its incident edges from a graph. For example, detach 3 g = [(1,2),(2,4)] and detach 2 h = [(1,3),(4,4)]
--------------------------------------------------------------------------------------------}
detach :: Node -> Graph -> Graph
detach x [] = []
detach x ((y1,y2):ys) | x == y1 = detach x ys
                      | x == y2   = detach x ys
                      | otherwise = (y1,y2) : detach x ys

{--------------------------------------------------------------------------------------------
- EX2: PART D
- Define the function cyc :: Int -> Graph that creates a cycle of any given number. 
- For example, cyc 4 = [(1,2),(2,3),(3,4),(4,1)].
--------------------------------------------------------------------------------------------}
bc :: Int -> Graph 
bc 1 = []
bc x = (bc (x-1) ++ [(x-1, x)])

cyc x = bc x ++ [(x,1)]

{- added from excersice -}
point = Pt (1,1)

circle = Circle (2,2) 2

rectangle = Rect (3,3) 3 3

f = [Pt (4,4), Circle (5,5) 3, Rect (3,3) 7 2]

{--------------------------------------------------------------------------------------------
- EX3: PART A 
- Define the function width that computes the width of a shape.
--------------------------------------------------------------------------------------------}
width :: Shape -> Length
width (Pt p)          = 0
width (Circle p l)    = l*2
width (Rect p l1 l2)  = l1

{--------------------------------------------------------------------------------------------
- EX3: PART B
- Define the function bbox that computes the bounding box of a shape.
--------------------------------------------------------------------------------------------}
bbox :: Shape -> BBox
bbox (Pt p)           = (p, p)
bbox (Circle p l)     = ((fst p - l, snd p - l),((fst p + l),(snd p + l)))
bbox (Rect p l1 l2)   = (p, ((fst p + l1),(snd p + l2)))

{--------------------------------------------------------------------------------------------
- EX3: PART C
- Define the function minX that computes the minimum x coordinate of a shape.
--------------------------------------------------------------------------------------------}
minX :: Shape -> Number
minX (Pt p) = fst p
minX (Rect p l1 l2) = fst p
minX (Circle p l) = fst p - l

{--------------------------------------------------------------------------------------------
- EX3: PART D
- Define a function move that moves the position of a shape by a vector given by a point as its second argument.
- It is probably a good idea to define and use an auxiliary function , which adds two points component wise.
--------------------------------------------------------------------------------------------}
move :: Shape -> Point -> Shape
move (Pt p) v = (Pt (addPt p v))
move (Rect p l1 l2) v = (Rect (addPt p v) l1 l2)
move (Circle p l) v  = (Circle (addPt p v) l)

addPt :: Point -> Point -> Point
addPt (x1,y1) (x2,y2) = (x1+x2,y1+y2)
