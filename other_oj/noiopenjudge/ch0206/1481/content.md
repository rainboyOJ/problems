## 描述


Given a set of n integers: A={a1, a2,..., an}, we define a function d(A) as below:                     t1     t2          d(A) = max{ ∑ai + ∑aj | 1 <= s1 <= t1 < s2 <= t2 <= n }                    i=s1   j=s2Your task is to calculate d(A).

## 输入


The input consists of T(<=30) test cases. The number of test cases (T) is given in the first line of the input. Each test case contains two lines. The first line is an integer n(2<=n<=50000). The second line contains n integers: a1, a2, ..., an. (|ai| <= 10000).There is an empty line after each case.

## 输出


Print exactly one line for each test case. The line should contain the integer d(A).

## 样例输入


```
1

10
1 -1 2 2 3 -3 4 -4 5 -5
```


## 样例输出


```
13
```


## 提示


In the sample, we choose {2,2,3,-3,4} and {5}, then we can get the answer.Huge input,scanf is recommended.

## 来源


POJ Contest,Author:Mathematica@ZSU

