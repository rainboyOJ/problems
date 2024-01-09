## 描述


The Frobozz Magic Lock Company is in the business of manufacturing push button style combination door locks. A push button door lock consists of a number of push buttons B, (1 ≤ B ≤ 11), labeled “1” through “B”. The lock is opened by pressing the correct sequence of button combinations and then turning the doorknob. If the sequence of presses is correct, the door magically opens. 

A combination consists of 1 or more buttons being pressed simultaneously. A sequence consists of a series of combinations. A sequence must have at least one combination. Once a button has been used in a combination, it may not be used again in the same sequence. In addition, it is not necessary to use all the buttons in a sequence. For example, for B = 8: 

(1-2-3)(4)(7-8) 

is a valid sequence with 3 combinations (1-2-3), (4), and (7-8). Note that buttons 5 and 6 are not used in this sequence. 

(1-2-3)(2-4)(5-6) 

is not a valid sequence, since button 2 appears in 2 combinations (1-2-3) and (2-4). 
The CEO of Frobozz, J. Pierpont Flathead, wants you to write a program that determines the number of valid sequences possible for given values of B. The program must be able to process a list of lock orders (datasets) from customers and generate a report showing the order number, the value of B, and the number of valid sequences possible. This list will always contain at least one dataset, but no more than 100 datasets. 

N个不同的数字，放到一些不同的BOX里面，数字你不必用完，Box的个数也是可变的.比如三个球，你可以只放一个BOX，也可以放二个或者三个，但是四个BOX那就不可能了.每个数字只能放到一个BOX里，问有多少种放法.


## 输入


The first line of input contains a  single integer N, (1 ≤ N ≤ 100), representing the number of datasets  that follow. Each dataset consists of a single line of data containing a  single integer B, which is the number of buttons for the lock. 

## 输出


 For each dataset, display the dataset number, a blank, the value B, a blank, and the number of valid sequences. 先输出是第几组数据，再输出这个数据的输入，再给出你的答案

## 样例输入


```
3
3
4
3
```


## 样例输出


```
1 3 25
2 4 149
3 3 25
```


## 提示


当有三个数字时，总有以下25种放法.1:当使用一个数字时，那么最多只能用一个BOX，因而有[1],[2],[3]这三种放法.2：当使用二个数字时，那么可以使用数字1,2，当只有一个BOX时有[1,2]这种放法，当使用二个时有[1],[2]或者[2],[1]这种放法；当然你也可以使用数字1,3或者2,3因而共有9种放法.3:当使用三个数字时，我就不推了，共有13种放法.综上，共有3+9+13=25种！

