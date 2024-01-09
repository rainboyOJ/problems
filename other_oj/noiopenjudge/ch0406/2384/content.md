## 描述


Farmer John has decided to give each of his cows a cell phone in hopes to encourage their social interaction. This, however, requires him to set up cell phone towers on his N (1 <= N <= 10,000) pastures (conveniently numbered 1..N) so they can all communicate.Exactly N-1 pairs of pastures are adjacent, and for any two pastures A and B (1 <= A <= N; 1 <= B <= N; A != B) there is a sequence of adjacent pastures such that A is the first pasture in the sequence and B is the last. Farmer John can only place cell phone towers in the pastures, and each tower has enough range to provide service to the pasture it is on and all pastures adjacent to the pasture with the cell tower.Help him determine the minimum number of towers he must install to provide cell phone service to each pasture.

## 输入


* Line 1: A single integer: N* Lines 2..N: Each line specifies a pair of adjacent pastures with two space-separated integers: A and B

## 输出


* Line 1: A single integer indicating the minimum number of towers to install

## 样例输入


```
5
1 3
5 2
4 3
3 5
```


## 样例输出


```
2

```


## 提示


INPUT DETAILS:Farmer John has 5 pastures: pastures 1 and 3 are adjacent, as are pastures 5 and 2, pastures 4 and 3, and pastures 3 and 5. Geometrically, the farm looks like this (or some similar configuration)               4  2               |  |            1--3--5OUTPUT DETAILS:The towers can be placed at pastures 2 and 3 or pastures 3 and 5.

## 来源


USACO January 2008 Gold

