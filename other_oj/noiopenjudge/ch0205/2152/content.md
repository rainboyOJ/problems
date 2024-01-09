## 描述


You are given two pots, having the volume of A and B liters respectively. The following operations can be performed:FILL(i)        fill the pot i (1 ≤ i ≤ 2) from the tap;DROP(i)      empty the pot i to the drain;POUR(i,j)    pour from pot i to pot j; after this operation either the pot j is full (and there may be some water left in the pot i), or the pot i is empty (and all its contents have been moved to the pot j).Write a program to find the shortest possible sequence of these operations that will yield exactly C liters of water in one of the pots.

## 输入


On the first and only line are the numbers A, B, and C. These are all integers in the range from 1 to 100 and C≤max(A,B).

## 输出


The first line of the output must contain the length of the sequence of operations K. The following K lines must each describe one operation. If there are several sequences of minimal length, output any one of them. If the desired result can’t be achieved, the first and only line of the file must contain the word ‘impossible’.

## 样例输入


```
3 5 4
```


## 样例输出


```
6
FILL(2)
POUR(2,1)
DROP(1)
POUR(2,1)
FILL(2)
POUR(2,1)
```


