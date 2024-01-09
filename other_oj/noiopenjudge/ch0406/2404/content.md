## 描述


Many staff of are living in a place called MZone, far from their office( 4.5 km ). Due to the bad traffic, many staff choose to ride a bike.We may assume that all the people except "Weiwei" ride from home to office at a fixed speed. Weiwei is a people with a different riding habit – he always tries to follow another rider to avoid riding alone. When Weiwei gets to the gate of MZone, he will look for someone who is setting off to the Office. If he finds someone, he will follow that rider, or if not, he will wait for someone to follow. On the way from his home to office, at any time if a faster student surpassed Weiwei, he will leave the rider he is following and speed up to follow the faster one.We assume the time that Weiwei gets to the gate of MZone is zero. Given the set off time and speed of the other people, your task is to give the time when Weiwei arrives at his office.

## 输入


There are several test cases. The first line of each case is N (1 <= N <= 10000) representing the number of riders (excluding Weiwei). N = 0 ends the input. The following N lines are information of N different riders, in such format: Vi [TAB] TiVi is a positive integer <= 40, indicating the speed of the i-th rider (kph, kilometers per hour). Ti is the set off time of the i-th rider, which is an integer and counted in seconds. In any case it is assured that there always exists a nonnegative Ti. 

## 输出


Output one line for each case: the arrival time of Weiwei. Round up (ceiling) the value when dealing with a fraction.

## 样例输入


```
4
20	0
25	-155
27	190
30	240
2
21	0
22	34
0

```


## 样例输出


```
780
771

```


