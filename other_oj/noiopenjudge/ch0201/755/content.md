## 描述


Flip game is played on a rectangular 4x4 field with two-sided pieces placed on each of its 16 squares. One side of each piece is white and the other one is black and each piece is lying either it's black or white side up. Each round you flip 3 to 5 pieces, thus changing the color of their upper side from black to white and vice versa. The pieces to be flipped are chosen every round according to the following rules:Choose any one of the 16 pieces. Flip the chosen piece and also all adjacent pieces to the left, to the right, to the top, and to the bottom of the chosen piece (if there are any). Consider the following position as an example:bwbwwwwwbbwbbwwbHere "b" denotes pieces lying their black side up and "w" denotes pieces lying their white side up. If we choose to flip the 1st piece from the 3rd row (this choice is shown at the picture), then the field will become:bwbwbwwwwwwbwwwbThe goal of the game is to flip either all pieces white side up or all pieces black side up. You are to write a program that will search for the minimum number of rounds needed to achieve this goal.

## 输入


The input consists of 4 lines with 4 characters "w" or "b" each that denote game field position.

## 输出


Write to the output file a single integer number - the minimum number of rounds needed to achieve the goal of the game from the given position. If the goal is initially achieved, then write 0. If it's impossible to achieve the goal, then write the word "Impossible" (without quotes).

## 样例输入


```
bwwb
bbwb
bwwb
bwww
```


## 样例输出


```
4

```


## 来源


Northeastern Europe 2000

