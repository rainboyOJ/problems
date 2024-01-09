## 描述


     1   2   3   4   5   6   7     ############################# 1 #   |   #   |   #   |   |   #   #####---#####---#---#####---# 2 #   #   |   #   #   #   #   #   #---#####---#####---#####---# 3 #   |   |   #   #   #   #   #   #---#########---#####---#---# 4 #   #   |   |   |   |   #   #   #############################(Figure 1)#  = Wall   |  = No wall-  = No wallFigure 1 shows the map of a castle.Write a program that calculates1. how many rooms the castle has2. how big the largest room isThe castle is divided into m * n (m<=50, n<=50) square modules. Each such module can have between zero and four walls. 

## 输入


Your program is to read from standard input. The first line contains the number of modules in the north-south direction and the number of modules in the east-west direction. In the following lines each module is described by a number (0 <= p <= 15). This number is the sum of: 1 (= wall to the west), 2 (= wall to the north), 4 (= wall to the east), 8 (= wall to the south). Inner walls are defined twice; a wall to the south in module 1,1 is also indicated as a wall to the north in module 2,1. The castle always has at least two rooms.

## 输出


Your program is to write to standard output: First the number of rooms, then the area of the largest room (counted in modules).

## 样例输入


```
4
7
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13
```


## 样例输出


```
5
9
```


## 来源


IOI 1994

