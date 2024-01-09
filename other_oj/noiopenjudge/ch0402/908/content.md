## 描述


Consider the set of all non-negative integer powers of 3. S = { 1, 3, 9, 27, 81, ... } Consider the sequence of all subsets of S ordered by the value of the sum of their elements. The question is simple: find the set at the n-th position in the sequence and print it in increasing order of its elements. 

## 输入


Each line of input contains a number n, which is a positive integer with no more than 19 digits. The last line of input contains 0 and it should not be processed. 

## 输出


For each line of input, output a single line displaying the n-th set as described above, in the format used in the sample output. 

## 样例输入


```
1
7
14
783
1125900981634049
0

```


## 样例输出


```
{ }
{ 3, 9 }
{ 1, 9, 27 }
{ 3, 9, 27, 6561, 19683 }
{ 59049, 3486784401, 205891132094649, 717897987691852588770249 }

```


## 来源


Waterloo local 2004.06.12

