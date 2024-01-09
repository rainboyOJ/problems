## 描述


Two players, Stan and Ollie, play, starting with two natural numbers. Stan, the first player, subtracts any positive multiple of the lesser of the two numbers from the greater of the two numbers, provided that the resulting number must be nonnegative. Then Ollie, the second player, does the same with the two resulting numbers, then Stan, etc., alternately, until one player is able to subtract a multiple of the lesser number from the greater to reach 0, and thereby wins. For example, the players may start with (25,7):          25 7         11 7          4 7          4 3          1 3          1 0an Stan wins. 

## 输入


The input consists of a number of lines. Each line contains two positive integers giving the starting two numbers of the game. Stan always starts.

## 输出


For each line of input, output one line saying either Stan wins or Ollie wins assuming that both of them play perfectly. The last line of input contains two zeroes and should not be processed.

## 样例输入


```
34 12
15 24
0 0

```


## 样例输出


```
Stan wins
Ollie wins

```


## 来源


Waterloo local 2002.09.28

