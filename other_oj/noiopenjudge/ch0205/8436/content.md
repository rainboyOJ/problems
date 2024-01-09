## 描述


《Journey to theWest》(also 《Monkey》) is one of the Four Great Classical Novelsof Chinese literature. It was writtenby Wu Cheng'en during the Ming Dynasty. In this novel, Monkey King Sun Wukong,pig Zhu Bajie and Sha Wujing, escorted Tang Monk to India to getsacred Buddhism texts. During thejourney, Tang Monk was often captured by demons. Most of demons wanted to eatTang Monk to achieve immortality, but some female demons just wanted to marryhim because he was handsome. So, fighting demons and saving Monk Tang is themajor job for Sun Wukong to do.Once, TangMonk was captured by the demon White Bones. White Bones lived in a palace andshe cuffed Tang Monk in a room. Sun Wukong managed to get into the palace. Butto rescue Tang Monk, Sun Wukong might need to get some keys and kill somesnakes in his way. The palace can be described as a matrix of characters. Each characterstands for a room. In the matrix, 'K' represents the original position of SunWukong, 'T' represents the location of Tang Monk and 'S' stands for a room witha snakein it. Please note that there are only one 'K' and one 'T', and at mostfive snakesin the palace. And, '.' means a clear room as well '#' means a deadlyroom which Sun Wukong couldn't get in. There may be some keys of different kinds scattered in the rooms, butthere is at most one key in one room. There are at most 9 kinds of keys. A roomwith a key in it is represented by a digit(from '1' to '9'). For example, '1'means a room with a first kind key, '2' means a room with a second kind key,'3' means a room with a third kind key... etc. To save Tang Monk, Sun Wukongmust get ALL kinds of keys(in other words, at least one key for each kind).  For each step, Sun Wukong couldmove to the adjacent rooms(except deadly rooms) in 4 directions(north, west, southand east), and each step took him one minute. If he entered a room in which aliving snakestayed, he must kill the snake.Killing a snakealso took one minute. If Sun Wukong entered a room where there is a keyof kind N, Sun would get that key if and only if he had already got keys ofkind 1,kind 2 ... and kind N-1. In other words, Sun Wukong must get a key ofkind N before he could get a key of kind N+1 (N>=1). If Sun Wukong got allkeys he needed and entered the room in which Tang Monk was cuffed, the rescue mission is completed. If Sun Wukong didn't get enough keys,he still could pass through Tang Monk's room. Since Sun Wukong was a impatient monkey,he wanted to save Tang Monk as quickly as possible. Please figure out theminimum time Sun Wukong needed to rescue Tang Monk.

## 输入


There are several test cases.For each case, the first line includes two integers N and M(0 < N <= 100, 0<=M<=9), meaning that the palace is a N×N matrix and Sun Wukong needed M kinds of keys(kind 1, kind 2, ... kind M). Then the N×N matrix follows.The input ends with N = 0 and M = 0.

## 输出


For each test case, print the minimum time (in minutes) Sun Wukong needed to save Tang Monk. If it's impossible for Sun Wukong to complete the mission, print "impossible"(no quotes).

## 样例输入


```
3 1
K.S
##1
1#T
3 1
K#T
.S#
1#.
3 2
K#T
.S.
21.
0 0

```


## 样例输出


```
5
impossible
8

```


## 来源


guo wei

