## 题目




### 题目描述

“Peter Pan frames” are a way of decorating text in which every character is framed by a diamond shaped frame, with frames of neigbhouring characters interleaving. A Peter Pan frame for one letter looks like this ('X' is the letter we are framing):
```
..#..
.#.#.
#.X.#
.#.#.
..#..
```
However, such a framing would be somewhat dull so we'll frame every third letter using a “Wendyframe”. A Wendy frame looks like this:

```
..*..
.*.*.
*.X.*
.*.*.
..*..
```
When a Wendy frame interleaves with a Peter Pan frame, the Wendy frame (being much nicer) is put on top. For an example of the interleaving check the sample cases.



### 输入格式
The first and only line of input will contain at most 15 capital letters of the English alphabet.



### 输出格式

Output the word written using Peter Pan and Wendy frames on 5 lines.



### 样例


输入/输出 # 1

::: line
```
A
```

```
..#..
.#.#.
#.A.#
.#.#.
..#..
```
:::

输入/输出 # 2

::: line
```
DOG
```

```
..#...#...*..
.#.#.#.#.*.*.
#.D.#.O.*.G.*
.#.#.#.#.*.*.
..#...#...*..
```
:::

输入/输出 # 3

::: line
```
ABCD
```

```
..#...#...*...#..
.#.#.#.#.*.*.#.#.
#.A.#.B.*.C.*.D.#
.#.#.#.#.*.*.#.#.
..#...#...*...#..
```
:::






## 来源

- [luogu P4327](https://www.luogu.com.cn/problem/P4327)
