## 描述


Acm, a treasure-explorer, is exploring again. This time he is in a special maze, in which there are some doors (at most 5 doors, represented by 'A', 'B', 'C', 'D', 'E' respectively). In order to find the treasure, Acm may need to open doors. However, to open a door he needs to find all the door's keys (at least one) in the maze first. For example, if there are 3 keys of Door A, to open the door he should find all the 3 keys first (that's three 'a's which denote the keys of 'A' in the maze). Now make a program to tell Acm whether he can find the treasure or not. Notice that Acm can only go up, down, left and right in the maze. 

## 输入


The input consists of multiple test cases. The first line of each test case contains two integers M and N (1 < N, M < 20), which denote the size of the maze. The next M lines give the maze layout, with each line containing N characters. A character is one of the following: 'X' (a block of wall, which the explorer cannot enter), '.' (an empty block), 'S' (the start point of Acm), 'G' (the position of treasure), 'A', 'B', 'C', 'D', 'E' (the doors), 'a', 'b', 'c', 'd', 'e' (the keys of the doors). The input is terminated with two 0's. This test case should not be processed. 

## 输出


For each test case, in one line output "YES" if Acm can find the treasure, or "NO" otherwise. 

## 样例输入


```
4 4 
S.X. 
a.X. 
..XG 
.... 
3 4 
S.Xa 
.aXB 
b.AG 
0 0

```


## 样例输出


```
YES 
NO

```


## 来源


POJ Monthly,Wang Yijie

