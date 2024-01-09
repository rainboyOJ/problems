## 描述


Determine the columns of N queens should be place on. Columns should be greater than 1 and less than N. Columns should be all different. Each column plus its index should be different from others. Each column minus its index should also be different from others.

## 输入


One positive integer number N (N <= 200).

## 输出


An N*N 0/1 matrix A = {a[i][j]}, a[i][j]=1 indicates that there is a queue on cell (i,j), and a[i][j]=0 otherwise.

## 样例输入


```
4
```


## 样例输出


```
0 1 0 0
0 0 0 1
1 0 0 0
0 0 1 0
```


