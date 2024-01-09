## 描述


A sequence of positive integers is Palindromic if it reads the same forward and backward. For example:23 11 15 1 37 37 1 15 11 231 1 2 3 4 7 7 10 7 7 4 3 2 1 1A Palindromic sequence is Unimodal Palindromic if the values do not decrease up to the middle value and then (since the sequence is palindromic) do not increase from the middle to the end For example, the first example sequence above is NOT Unimodal Palindromic while the second example is.A Unimodal Palindromic sequence is a Unimodal Palindromic Decomposition of an integer N, if the sum of the integers in the sequence is N. For example, all of the Unimodal Palindromic Decompositions of the first few integers are given below:1: (1)2: (2), (1 1)3: (3), (1 1 1)4: (4), (1 2 1), (2 2), (1 1 1 1)5: (5), (1 3 1), (1 1 1 1 1)6: (6), (1 4 1), (2 2 2), (1 1 2 1 1), (3 3),(1 2 2 1), ( 1 1 1 1 1 1)7: (7), (1 5 1), (2 3 2), (1 1 3 1 1), (1 1 1 1 1 1 1)8: (8), (1 6 1), (2 4 2), (1 1 4 1 1), (1 2 2 2 1),(1 1 1 2 1 1 1), ( 4 4), (1 3 3 1), (2 2 2 2),(1 1 2 2 1 1), (1 1 1 1 1 1 1 1)Write a program, which computes the number of Unimodal Palindromic Decompositions of an integer.

## 输入


Input consists of a sequence of positive integers, one per line ending with a 0 (zero) indicating the end.

## 输出


For each input value except the last, the output is a line containing the input value followed by a space, then the number of Unimodal Palindromic Decompositions of the input value. See the example on the next page.

## 样例输入


```
2
3
4
5
6
7
8
10
23
24
131
213
92
0
```


## 样例输出


```
2 2
3 2
4 4
5 3
6 7
7 5
8 11
10 17
23 104
24 199
131 5010688
213 1055852590
92 331143
```


## 提示


N < 250

## 来源


Greater New York 2002

