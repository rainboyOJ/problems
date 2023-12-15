## 题目描述

![](https://ww1.sinaimg.cn/large/007i4MEmly1g1ivm0s931j30lv06kabs.jpg)

在家里用电视机做字母游戏是很流行的,其中一种玩法是:每一个字母有一个数值与之对应.你收集字母组成一个或多个字以得到尽可能高的得分.除非你已有了 “找字的方法”(“a way with words”),你会把你知道的字都试一遍.有时你也许会查阅其拼写,然后计算得分.显然可以用计算机更为准确地完成此任务.上图示出了英文字母及其所对应的值,当给出英文字(word) 的表列及收 集的字母时,请找出所能形成的得分最高的字或字对(pairs of words).

## INPUT FORMAT

输入文件 lgame.in 中有一行由小写字母(`A'到`Z')组成的字符串, 这就是收集到字母(就是可以使用的字母),字符串由至少 3 个字母至多 7 个字母(以任意顺序) 组成.字典文件 lgame.dict
由至多 40,000 行组成,文件的最后一行有'.' 表示文件的结束.文件中的字已按字母顺序排序.其
它各行每一行都是由至少 3 个小写字母,至多 7 个小写字母组成的字符串.文件中的字已按字母顺序排序.

## SAMPLE INPUT (file lgame.in)

```
prmgroa
```
## SAMPLE INPUT (file lgame.dict)
```
profile
program
prom
rag
ram
rom
.
```

## OUTPUT FORMAT

在文件 lgame.out 的第一行,你的程序应写上最高得分(子任务 A), 随后的每一行是由文件words.txt中查到的具有这个得分的所有的字和或字对(word pairs)(子任务 B).要利用图中给定的
字母的值.当两个字能够形成 一个组合(具有给定的字母)时,这两个字应该打印到同一行,两个字
中间用一个空格隔开.不许重复表示字对,例如'rag prom'和'prom rag'是同样的字对,因此只应该
写出其中的一个.

## SAMPLE OUTPUT (file lagame.out)
```
24
program
prom rag 
```
