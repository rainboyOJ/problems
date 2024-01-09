## 描述


BackgroundMr Somurolov, fabulous chess-gamer indeed, asserts that no one else but him can move knights from one position to another so fast. Can you beat him?The ProblemYour task is to write a program to calculate the minimum number of moves needed for a knight to reach one point from another, so that you have the chance to be faster than Somurolov.For people not familiar with chess, the possible knight moves are shown in Figure 1.

## 输入


The input begins with the number n of scenarios on a single line by itself.Next follow n scenarios. Each scenario consists of three lines containing integer numbers. The first line specifies the length l of a side of the chess board (4 <= l <= 300). The entire board has size l * l. The second and third line contain pair of integers {0, ..., l-1}*{0, ..., l-1} specifying the starting and ending position of the knight on the board. The integers are separated by a single blank. You can assume that the positions are valid positions on the chess board of that scenario.

## 输出


For each scenario of the input you have to calculate the minimal amount of knight moves which are necessary to move from the starting point to the ending point. If starting point and ending point are equal,distance is zero. The distance must be written on a single line.

## 样例输入


```
3
8
0 0
7 0
100
0 0
30 50
10
1 1
1 1
```


## 样例输出


```
5
28
0
```


## 来源


TUD Programming Contest 2001, Darmstadt, Germany

