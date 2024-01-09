## 描述


The well-known magician David Copperfield loves to show the following trick: a square with N rows and N columns of different pictures appears on a TV screen. Let us number all the pictures in the following order: 12...N::...:N*(N-1)+1N*(N-1)+2...N*NEach member of the audience is asked to put a finger on the upper left picture (i.e., picture number one) and The Magic begins: the magician tells the audience to move the finger k1 times through the pictures (each move is a shift of the finger to the adjacent picture up, down, left or right provided that there is a picture to move to), then with a slight movement of his hand he removes some of the pictures with an exclamation "You are not there!", and ... it is true - your finger is not pointing to any of the pictures removed. Then again, he tells the audience to make k2 moves, and so on. At the end he removes all the pictures but one and smiling triumphantly declares, "I've caught you" (applause). Just now, David is trying to repeat this trick. Unfortunately, he had a hard day before, and you know how hard to conjure with a headache. You have to write a program that will help David to make his trick. 

## 输入


The input contains a single integer number N (2<=N<=100). 

## 输出


Your program should write the following lines with numbers to the output file: k1 x1,1 x1,2 ... x1,m1k2 x2,1 x2,2 ... x2,m2   ...ke xe,1 xe,2 ... xe,mewhere ki is a number of moves the audience should make on the i-th turn (2N<=k<=10000). All ki should be different (i.e. ki <> kj when i <> j). xi,1, xi,2, ... , xi, mi are the numbers of the pictures David should remove after the audience will make ki moves (the number of the pictures removed is arbitrary, but each picture should be listed only once, and at least one picture should be removed on each turn). A description of the every next turn should begin with a new line. All numbers on each line should be separated by one space. After e iterations, all pictures except one should be removed. 

## 样例输入


```
3

```


## 样例输出


```
8 4 6
13 9
10 7 1
7 8
11 3 5

```


## 来源


Northeastern Europe 1997

