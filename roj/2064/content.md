## 题目描述

农民 Brown和 John的牛们计划协同逃出它们各自的农场.它们设计了一种加密方法用来保护它们的通讯不被他人知道.

如果一头牛有信息要加密,比如"International Olympiad in Informatics",它会随机地把 C,O,W 三个字母插到到信息中（其中C在O 前面,O 在 W 前面）,然后它把C与O 之间的文字和 O 与 W 之间的文字的位置换过来.这里是两个例子:

```
International Olympiad in Informatics
->
CnOIWternational Olympiad in Informatics
International Olympiad in Informatics
->
International Cin InformaticsOOlympiad W
```

为了使解密更复杂,牛们会在一条消息里多次采用这个加密方法（把上次加密的结果再进行加密）.

一天夜里,John 的牛们收到了一条经过多次加密的信息.请你写一个程序判断它是不是这条信息经过加密（或没有加密）而得到的:

```
Begin the Escape execution at the Break of Dawn
```

## INPUT FORMAT

一行,不超过 75 个字符的加密过的信息.

## SAMPLE INPUT(file cryptcow.in)

```
Begin the EscCution at the BreOape execWak of Dawn
```

## OUTPUT FORMAT

一行,两个整数. 如果能解密成上面那条逃跑的信息,第一个整数应当为 1,否则为 0；如果第一个数为 1,则第二个数表示此信息被加密的次数,否则第二个数为 0.

## SAMPLE OUTPUT(file cryptcow.out)
```
1 1 
```
