## 描述


Professor John is investigating a math problem. He has obtained some relations among several variables. Now he would like to know if there are any other relations that can be deduced from these obtained ones. For example, the known relations are given as follows: A < B, C > B and C < D, other relations including A < C, A < D and B < D can be deduced. Since he has been working for too long, Professor John decides to grant himself a vacation while assigning you to do the job. Are you ready?

## 输入


The first line of input contains an integer N, which is the number of test cases. Then N test cases follow. For each test case: the 1st line contains a positive integer m (<= 100) which is the number of given relations; the following m lines each contains a given relation, in the format Variable1 < Variable2 or Variable1 > Variable2A "Variable" is represented by a capital character. There will not be conflicting relations given.

## 输出


For each test case, first print in one line "Case d:" where d is the number of the test case, start counting from 1. Then output all the relations which can be deduced from the given relations in alphabetical order, in the format Variable1 < Variable2. Each relation occupies one line. No extra space shall be printed. The given relations must NOT be included. If no new relation is found, output "NONE" in one line.

## 样例输入


```
2
3
A<B
C>B
C<D
2
A<B
C<D

```


## 样例输出


```
Case 1:
A<C
A<D
B<D
Case 2:
NONE

```


