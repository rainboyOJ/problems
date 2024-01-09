## 描述


There are N cities in the graph. Given the length and the cost of each edge. Find path from city 1 to city N. The length of the path should be shortest and the cost of it should be less than M.

## 输入


First line: two positive integers N (N <= 100) and M (M <= 1000).Next N lines: the i-th line contains N integers indicating the length of edge between city i and other cities.Next N lines: the i-th line contains N integers indicating the cost of edge between city i and other cities.

## 输出


One line contains several integers, indicating the indexes of cities in the path.

## 样例输入


```
3 4
0 2 1
2 0 2
1 2 0
0 2 5
2 0 2
5 2 0

```


## 样例输出


```
1 2 3
```


