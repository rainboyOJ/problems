## 描述


A man arrives at a bus stop at 12:00. He remains there during 12:00-12:59. The bus stop is used by a number of bus routes. The man notes the times of arriving buses. The times when buses arrive are given. 	Buses on the same route arrive at regular intervals from 12:00 to 12:59 throughout the entire hour. 	Times are given in whole minutes from 0 to 59. 	Each bus route stops at least 2 times. 	The number of bus routes in the test examples will be <=17. 	Buses from different routes may arrive at the same time. 	Several bus routes can have the same time of first arrival and/or time interval. If two bus routes have the same starting time and interval, they are distinct and are both to be presented. Find the schedule with the fewest number of bus routes that must stop at the bus stop to satisfy the input data. For each bus route, output the starting time and the interval. 

## 输入


Your program is to read from standard input. The input contains a number n (n <= 300) telling how many arriving buses have been noted, followed by the arrival times in ascending order. 

## 输出


Your program is to write to standard output. The output contains one integer, which is the fewest number of bus routes.

## 样例输入


```
17
0 3 5 13 13 15 21 26 27 29 37 39 39 45 51 52 53
```


## 样例输出


```
3
```


## 来源


IOI 1994

