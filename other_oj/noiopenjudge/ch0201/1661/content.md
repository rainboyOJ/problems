## 描述


Bosko and Susko are playing an interesting game on a board made of rectangular fields arranged in A rows and B columns.When the game starts, Susko puts its virtual pillbox in one field one the board. Then Bosko selects fields on which he will throw his virtual bombs. After each bomb, Susko will tell Bosko whether his pillbox is in the range of this bomb or not.The range of a bomb with diameter P (P is always odd), which is thrown in field (R, S), is a square area. The center of the square is in the field (R, S), and the side of the square is parallel to the sides of the board and with length P.After some bombs have been thrown, Bosko should find out the position of Susko's pillbox. However, the position may be not unique, and your job is to help Bosko to calculate the number of possible positions.

## 输入


First line of input contains three integers: A, B and K, 1 <= A, B, K <=100. A represents the number of rows, B the number of columns and K the number of thrown bombs.Each of the next K lines contains integers R, S, P and T, describing a bomb thrown in the field at R-th row and S-th column with diameter P, 1 <= R <= A, 1 <= S <= B, 1 <= P <= 99, P is odd. If the pillbox is in the range of this bomb, T equals to 1; otherwise it is 0.

## 输出


Output the number of possible fields, which Susko's pillbox may stay in.

## 样例输入


```
5 5 3
3 3 3 1
3 4 1 0
3 4 3 1

```


## 样例输出


```
5
```


## 来源


Croatia OI 2002 National – Juniors

