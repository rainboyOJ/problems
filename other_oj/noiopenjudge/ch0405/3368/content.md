## 描述


After East Han dynasty, China was divided into several states. Wei, Wu, and Shu are the greatest three states among them. This was the era of Sanguo. During this period, wars frequently happened between states. Zhuge Liang, the commander and strategist of Shu, wanted to enlarge Shu's power. He was considering conquering N cities. However, these cities must be defeated in a specified order. City-X could be defeated only after City-1, City-2, City-3 ... City-(X-1) had been defeated. However, passing through the cities that had not been defeated was eligible. Zhuge wanted to use three generals, Guan Yu, Zhang Fei, and Zhao yun, each of whom should lead an army. The three armies, started from Yizhou, which was numbered with City-0. After conquered all the N cities (each cities must be conquered at least by one army), they had to return to Yizhou.The N cities and Yizhou were connected by M bi-directed roads. To travel from city to city was a very boring and expensive thing. So Zhuge wanted to minimize the total length of the three armies' traveling. You were hired to help him to compute the minimum total length of the traveling.

## 输入


Line1: two integers N and M. N is the number of cities Zhuge wanted to conquer, and M is the number of roads between the N + 1 cities.Line2...Line(M+1): each line contain 3 integers, X, Y, Len, indicating a road between City-X and City-Y, with the length of Len.You can suppose that all the N + 1 cities are connected.N ≤ 500, M ≤ 20000, Len ≤ 1000

## 输出


Line1: an integer, which is the minimum total length of the three armies' traveling.

## 样例输入


```
5 15
5 5 48
1 4 658
4 0 843
1 4 41
1 4 330
5 2 864
4 2 115
4 0 303
2 3 685
0 0 879
1 5 649
2 4 942
4 0 379
5 2 769
5 1 856

```


## 样例输出


```
3668
```



```
After East Han dynasty, China was divided into several states. Wei, Wu, and Shu are the greatest three states among them. This was the era of Sanguo. During this period, wars frequently happened between states. Zhuge Liang, the commander and strategist of Shu, wanted to enlarge Shu's power. He was considering conquering N cities. However, these cities must be defeated in a specified order. City-X could be defeated only after City-1, City-2, City-3 ... City-(X-1) had been defeated. However, passing through the cities that had not been defeated was eligible. Zhuge wanted to use three generals, Guan Yu, Zhang Fei, and Zhao yun, each of whom should lead an army. The three armies, started from Yizhou, which was numbered with City-0. After conquered all the N cities (each cities must be conquered at least by one army), they had to return to Yizhou.
```



```
The N cities and Yizhou were connected by M bi-directed roads. To travel from city to city was a very boring and expensive thing. So Zhuge wanted to minimize the total length of the three armies' traveling. You were hired to help him to compute the minimum total length of the traveling.
```


