## 描述


Solitaire is a game played on a chessboard 8x8. The rows and columns of the chessboard are numbered from 1 to 8, from the top to the bottom and from left to right respectively. There are four identical pieces on the board. In one move it is allowed to: move a piece to an empty neighboring field (up, down, left or right), jump over one neighboring piece to an empty field (up, down, left or right). There are 4 moves allowed for each piece in the configuration shown above. As an example let's consider a piece placed in the row 4, column 4. It can be moved one row up, two rows down, one column left or two columns right. Write a program that: reads two chessboard configurations from the standard input, verifies whether the second one is reachable from the first one in at most 8 moves, writes the result to the standard output. 

## 输入


Each of two input lines contains 8 integers a1, a2, ..., a8 separated by single spaces and describes one configuration of pieces on the chessboard. Integers a2j-1 and a2j (1 <= j <= 4) describe the position of one piece -- the row number and the column number respectively.

## 输出


The output should contain one word YES if a configuration described in the second input line is reachable from the configuration described in the first input line in at most 8 moves, or one word NO otherwise.

## 样例输入


```
4 4 4 5 5 4 6 5
2 4 3 3 3 6 4 6
```


## 样例输出


```
YES
```


## 来源


Southwestern Europe 2002

