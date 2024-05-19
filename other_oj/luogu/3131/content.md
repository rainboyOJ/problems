## 题目




### 题目描述

Farmer John's $N$ cows are standing in a row, as they have a tendency to do from time to time.  Each cow is labeled with a distinct integer ID number so FJ can tell them apart. FJ would like to take a photo of a contiguous group of cows but, due to a traumatic  childhood incident involving the numbers $1 \ldots 6$, he only wants to take a picture of a group of cows if their IDs add up to a multiple of 7.


Please help FJ determine the size of the largest group he can photograph.

给你n个数，分别是a[1],a[2],...,a[n]。求一个最长的区间[x,y]，使得区间中的数(a[x],a[x+1],a[x+2],...,a[y-1],a[y])的和能被7整除。输出区间长度。若没有符合要求的区间，输出0。





### 输入格式
The first line of input contains $N$ ($1 \leq N \leq 50,000$).  The next $N$

lines each contain the $N$ integer IDs of the cows (all are in the range

$0 \ldots 1,000,000$).




### 输出格式

Please output the number of cows in the largest consecutive group whose IDs sum

to a multiple of 7.  If no such group exists, output 0.




### 样例


输入/输出 # 1

::: line
```
7
3
5
1
6
2
14
10
```

```
5
```
:::





### 说明/提示
In this example, 5+1+6+2+14 = 28.



## 来源

- [luogu P3131](https://www.luogu.com.cn/problem/P3131)
