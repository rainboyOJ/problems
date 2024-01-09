## 描述


You are trapped in a 3D dungeon and need to find the quickest way out! The dungeon is composed of unit cubes which may or may not be filled with rock. It takes one minute to move one unit north, south, east, west, up or down. You cannot move diagonally and the maze is surrounded by solid rock on all sides. Is an escape possible? If yes, how long will it take? 

## 输入


The input consists of a number of dungeons. Each dungeon description starts with a line containing three integers L, R and C (all limited to 30 in size). L is the number of levels making up the dungeon. R and C are the number of rows and columns making up the plan of each level. Then there will follow L blocks of R lines each containing C characters. Each character describes one cell of the dungeon. A cell full of rock is indicated by a '#' and empty cells are represented by a '.'. Your starting position is indicated by 'S' and the exit by the letter 'E'. There's a single blank line after each level. Input is terminated by three zeroes for L, R and C. 

## 输出


Each maze generates one line of output. If it is possible to reach the exit, print a line of the form Escaped in x minute(s). where x is replaced by the shortest time it takes to escape. If it is not possible to escape, print the line Trapped! 

## 样例输入


```
3 4 5
S....
.###.
.##..
###.#

#####
#####
##.##
##...

#####
#####
#.###
####E

1 3 3
S##
#E#
###

0 0 0

```


## 样例输出


```
Escaped in 11 minute(s).
Trapped!

```


## 来源


Ulm Local 1997

