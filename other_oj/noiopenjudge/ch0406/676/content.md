## 描述


Given a permutation of numbers from 1 to n, we can always get the sequence 1, 2, 3, ..., n by swapping pairs of numbers. For example, if the initial sequence is 2, 3, 5, 4, 1, we can sort them in the following way:2 3 5 4 11 3 5 4 21 3 2 4 51 2 3 4 5Here three swaps have been used. The problem is, given a specific permutation, how many swaps we needs to take at least. 

## 输入


The first line contains a single integer t (1 <= t <= 20) that indicates the number of test cases. Then follow the t cases. Each case contains two lines. The first line contains the integer n (1 <= n <= 10000), and the second line gives the initial permutation.

## 输出


For each test case, the output will be only one integer, which is the least number of swaps needed to get the sequence 1, 2, 3, ..., n from the initial permutation. 

## 样例输入


```
2
3
1 2 3
5
2 3 5 4 1
```


## 样例输出


```
0
3
```


## 来源


POJ Monthly--2004.06.27 弱人

