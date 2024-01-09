## 描述


ZSoft Corp. is a software company in GaoKe Hall. And the workers in the hall are very hard-working. But the elevator in that hall always drives them crazy. Why? Because there is only one elevator in GaoKe Hall, while there are hundreds of companies in it. Every morning, people must waste a lot of time waiting for the elevator.Hal, a smart guy in ZSoft, wants to change this situation. He wants to find a way to make the elevator work more effectively. But its not an easy job.There are H floors in GaoKe Hall. It takes 4 seconds for the elevator to raise one floor. It means:It costs (n-1)*4seconds if the elevator goes from the 1 st floor to the nth floor without stop. And the elevator stops 10 second once. So, if the elevator stops at each floor, it will cost (n-1)*4+(n-2)*10seconds (It is not necessary to calculate the stopping time at nth floor). In another way, it takes 20 seconds for the workers to go up or down one floor. It takes (n-1)*20seconds for them to walk from the 1 st floor to the nth floor. Obviously, it is not a good idea. So some people choose to use the elevator to get a floor which is the nearest to their office.After thinking over for a long time, Hal finally found a way to improve this situation. He told the elevator man his idea: First, the elevator man asks the people which floors they want to go. He will then design a stopping plan which minimize the time the last person need to arrive the floor where his office locates. For example, if the elevator is required to stop at the 4 th , 5 th and 10 th floor, the stopping plan would be: the elevator stops at 4 th and 10 th floor. Because the elevator will arrive 4 th floor at 3*4=12second, then it will stop 10 seconds, then it will arrive 10 th floor at 3*4+10+6*4=46second. People who want to go 4 th floor will reach their office at 12second, people who want to go to 5 th floor will reach at 12+20=32second and people who want to go to 10 th floor will reach at 46 second. Therefore it takes 46 seconds for the last person to reach his office. It is a good deal for all people.Now, you are supposed to write a program to help the elevator man to design the stopping plan,which minimize the time the last person needs to arrive at his floor.

## 输入


The input consists of several test cases. Each test case is in a single line as the following:n f1 f2 ... fnIt means, there are totally n floors at which the elevator need to stop, and n = 0 means no testcases any more. f1 f2 ... fn are the floors at which the elevator is to be stopped (1<=n<=30000, 2<=f1< f2 ... fn<=30000). Every number is separated by a single space.

## 输出


For each testcase, output the time the last reading person needs in the a single line

## 样例输入


```
3 4 5 10
1 2
0

```


## 样例输出


```
46
4

```


## 来源


LouTiancheng@POJ

