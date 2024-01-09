## 描述


Daxinganling produces a lot of timber. Before loading onto trains, the timberjacks will place the logs to some place in the open air first. Looking from the sideway, the figure of a logs stack is as follows: 
We have known that the number of logs in each layer is fewer than the lower layer for at least one log, and that in each layer the logs are connected in a line. In the figure above, there are 12 logs in the bottom layer of the stack. Now, given the number of logs in the bottom layer, the timberjacks want to know how many possible figures there may be. 
给出在最底层的木头的个数，问有多少种堆放木头的方式，当然你的堆放方式不能让木头掉下来. 
在堆放的时候木头必须互相挨着在一起. 


## 输入


The  first line of input contains the number of test cases T (1 <= T  <= 1000000). Then T lines follow. Every line only contains a number n  (1 <= n <= 200000) representing the number of logs in the bottom  layer. 

## 输出


For each test case in the input, you  should output the corresponding number of possible figures. Because the  number may be very large, just output the number mod 10^5. 

## 样例输入


```
4
1
2
3
5
```


## 样例输出


```
1
2
5
34
```


## 提示


当输入3时，有5种方式第一种：上面一个也不放第二种：上面放一根，放在最左边第三种：上面放一根，放在最右边第四种：上面放二根第五种：上面先放二根，然后在二根的上面放一根

