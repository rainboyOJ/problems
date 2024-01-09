## 描述


Given a sequence of N nonnegative integers. Let's define the median of such sequence. If N is odd the median is the element with stands in the middle of the sequence after it is sorted. One may notice that in this case the median has position (N+1)/2 in sorted sequence if sequence elements are numbered starting with 1. If N is even then the median is the semi-sum of the two "middle" elements of sorted sequence. I.e. semi-sum of the elements in positions N/2 and (N/2)+1 of sorted sequence. But original sequence might be unsorted.Your task is to write program to find the median of given sequence. 

## 输入


The first line of input contains the only integer number N - the length of the sequence. Sequence itself follows in subsequent lines, one number in a line. The length of the sequence lies in the range from 1 to 250000. Each element of the sequence is a positive integer not greater than 2^32 - 1 inclusive. 

## 输出


You should print the value of the median with exactly one digit after decimal point. 

## 样例输入


```
4
3
6
4
5

```


## 样例输出


```
4.5
```


## 提示


Huge input,scanf is recommended.

## 来源


Ural Collegiate Programming Contest 1998

