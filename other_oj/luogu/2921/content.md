## 题目




### 题目描述

Every year in Wisconsin the cows celebrate the USA autumn holiday of Halloween by dressing up in costumes and collecting candy that Farmer John leaves in the N (1 <= N <= 100,000) stalls conveniently numbered 1..N.

Because the barn is not so large, FJ makes sure the cows extend their fun by specifying a traversal route the cows must follow.  To implement this scheme for traveling back and forth through the barn, FJ has posted a 'next stall number' next\_i (1 <= next\_i <= N) on stall i that tells the cows which stall to visit next; the cows thus might travel the length of the barn many times in order to collect their candy.

FJ mandates that cow i should start collecting candy at stall i. A cow stops her candy collection if she arrives back at any stall she has already visited.

Calculate the number of unique stalls each cow visits before being forced to stop her candy collection.

POINTS: 100



### 输入格式
\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 contains a single integer: next\_i




### 输出格式

\* Lines 1..N: Line i contains a single integer that is the total number of unique stalls visited by cow i before she returns to a stall  she has previously visited.




### 样例


输入/输出 # 1

::: line
```
4 
1 
3 
2 
3 

```

```
1 
2 
2 
3 

```
:::





### 说明/提示
Four stalls.

\* Stall 1 directs the cow back to stall 1.

\* Stall 2 directs the cow to stall 3

\* Stall 3 directs the cow to stall 2

\* Stall 4 directs the cow to stall 3


Cow 1:  Start at 1, next is 1.  Total stalls visited: 1.

Cow 2:  Start at 2, next is 3, next is 2.  Total stalls visited: 2. Cow 3:  Start at 3, next is 2, next is 3.  Total stalls visited: 2. Cow 4:  Start at 4, next is 3, next is 2, next is 3. Total stalls visited: 3.



## 来源

- [luogu P2921](https://www.luogu.com.cn/problem/P2921)
