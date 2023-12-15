## 题目描述

在威斯康辛州牛大农场经营者之中,都习惯于请会计部门用连续数字给母牛打上烙印.
但是,母牛用手机时并没感到这个系统的便利,它们更喜欢用它们喜欢的名字来呼叫它们的同伴,而
不是用像这个的语句"C'mon, #4734, get along.".
请写一个程序来帮助可怜的牧牛工将一只母牛的烙印编号翻译成一个可能的名字.
因为母牛们现在都有手机了,使用那标准的按键的排布来把收到从数目翻译到文字:( 除了为之外
"Q" 和 "Z")
```
 2: A,B,C 5: J,K,L 8: T,U,V
 3: D,E,F 6: M,N,O 9: W,X,Y
 4: G,H,I 7: P,R,S
```
可接受的名字都被放在这样一个叫作 dict.txt 的文件中,它包含一连串的少于 5000 个可接受的牛
名字.(所有的名字都是大写的),收到母牛的编号返回那些能从编号翻译出来并且在字典中的名字.
举例来说,编号 4734 能产生的下列各项名字:

```
GPDG GPDH GPDI GPEG GPEH GPEI GPFG GPFH GPFI GRDG GRDH GRDI
GREG GREH GREI GRFG GRFH GRFI GSDG GSDH GSDI GSEG GSEH GSEI
GSFG GSFH GSFI HPDG HPDH HPDI HPEG HPEH HPEI HPFG HPFH HPFI
HRDG HRDH HRDI HREG HREH HREI HRFG HRFH HRFI HSDG HSDH HSDI
HSEG HSEH HSEI HSFG HSFH HSFI IPDG IPDH IPDI IPEG IPEH IPEI
IPFG IPFH IPFI IRDG IRDH IRDI IREG IREH IREI IRFG IRFH IRFI
ISDG ISDH ISDI ISEG ISEH ISEI ISFG ISFH ISFI
```
碰巧,81 个中只有一个"GREG"是有效的(在字典中).
Challenge One
写一个程序来对给出的编号打印出所有的有效名字,如果没有则输出"NONE'' .
编号可能有 12 位数字. 

## INPUT FORMAT
单独的一行包含一个编号(长度可能从 1 到 12).

## SAMPLE INPUT (file namenum.in)
```
4734
```
## OUTPUT FORMAT
以字典顺序输出一个有效名字的不负列表,一行一个名字.

## SAMPLE OUTPUT (file namenum.out)
```
GREG
```
