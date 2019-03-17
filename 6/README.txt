HOMEWORK 6: CROSSWORD BLACKOUT

resources:
http://www.cplusplus.com/reference/vector/vector/vector/
https://www.hackerrank.com/challenges/vector-erase/problem
http://www.cplusplus.com/reference/algorithm/find/
http://www.cplusplus.com/reference/vector/vector/insert/
http://www.cplusplus.com/reference/vector/vector/erase/
https://www.mathsisfun.com/combinatorics/combinations-permutations.html
https://www.jb51.net/article/54443.htm
https://stackoverflow.com/questions/33829922/c-delete-pointer-and-then-access-the-value-of-it-points-to
https://stackoverflow.com/questions/15730827/how-to-detect-if-a-pointer-was-deleted-and-securely-delete-it
https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector


Notes:

For making combinations(function combination), number of combinations, C(n,r), equals to n!/r!(n-r)!.(combinations choosing r elements out of n) And i also do words checking in the two functions. That will add up the complexity, or reduce in the case that it does help the recursive function to avoid keep going if the words are invalid already checkSolution function's complexity depends on size of the vector "solution"

checkSolution has been used throughout the function findSolutions to control the size of vectors and make them significantly smaller. Some more improvements can still be made. For example, in finding words, "#" can be skipped

Description of my test cases:

my_d.txt
MNO
CHM
FKP
INS
EJOT
ABCD
GHIJ
BGLQ
PQRST

my_p.txt
+3
+4
+5
ABCDE
FGHIJ
KLMNO
PQRST

Testing:

1.
F
K
PQRST

2.(Wrong)
ABCD
F
K
P

3.
    E
    J
    O
PQRST

4.(Wrong)
FGHIJ
K
Q

5.(Wrong)
  C
  H
  M
PQRST

6.(Wrong)
  MNO
PQRST

7.(Wrong)
   E
   IJ
   NO
   ST

my_p_noSolution.txt
+3
+3
+4
+4
+5
ABCDE
FGHIJ
KLMNO
PQRST

Testing Constraints conflicts

my_d2.txt
BEN
BENJ
BENJOMGD
ENJO
ABOUT
COMP
COMPUTER
TITLE
POOL
RENT
PUTJO
PUTJ
ENDO
COMB

my_p2.txt
+8
+5
+4
+4
+4
COMBO
O##E#
M##N#
PUTJO
U##O#
T##M#
E##G#
RENDO

p2 and d2 test substrings combinations vertical and "word turn"

my_d3.txt
BEN
BENJ
BENJOMGD
ENJO
COMP
COMPUTER
RENT
ENDO
COMB
COMBB
RENTD

my_p3.txt
+8
+5
+4
+4
COMPUTER
O######E
M######N
B######T
BENJOMGD

d3 and p3 test substrings combinations horizontal + vertical and "word turn"


Dictionary: my_d.txt
Puzzle: my_p.txt
Solution mode: all solutions
# of solutions: 3
Time: finished instantly

Dictionary: my_d.txt
Puzzle: my_p_noSolution.txt
Solution mode: all solutions
# of solutions: 0
Time: finished instantly

Dictionary: my_d2.txt
Puzzle: my_p2.txt
Solution mode: all solutions
# of solutions: 1
Time: finished instantly

Dictionary: my_d3.txt
Puzzle: my_p3.txt
Solution mode: all solutions
# of solutions: 2
Time: finished instantly

