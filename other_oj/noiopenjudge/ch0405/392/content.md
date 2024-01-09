## 描述


Some of you may have played a game called 'Blocks'. There are n blocks in a row, each box has a color. Here is an example: Gold, Silver, Silver, Silver, Silver, Bronze, Bronze, Bronze, Gold. The corresponding picture will be as shown below: Figure 1If some adjacent boxes are all of the same color, and both the box to its left(if it exists) and its right(if it exists) are of some other color, we call it a 'box segment'. There are 4 box segments. That is: gold, silver, bronze, gold. There are 1, 4, 3, 1 box(es) in the segments respectively. Every time, you can click a box, then the whole segment containing that box DISAPPEARS. If that segment is composed of k boxes, you will get k*k points. for example, if you click on a silver box, the silver segment disappears, you got 4*4=16 points. Now let's look at the picture below: Figure 2The first one is OPTIMAL. Find the highest score you can get, given an initial state of this game.

## 输入


The first line contains the number of tests t(1<=t<=15). Each case contains two lines. The first line contains an integer n(1<=n<=200), the number of boxes. The second line contains n integers, representing the colors of each box. The integers are in the range 1~n.

## 输出


For each test case, print the case number and the highest possible score.

## 样例输入


```
2
9
1 2 2 2 2 3 3 3 1
1
1
```


## 样例输出


```
Case 1: 29
Case 2: 1
```


## 来源


Liu Rujia@POJ

