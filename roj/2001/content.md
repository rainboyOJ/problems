## 题目描述

对于一群要互送礼物的朋友,你要确定每个人送出的礼物比收到的多多少(and vice versa for
those who view gift giving with cynicism).
在这一个问题中,每个人都准备了一些钱来送礼物,而这些钱将会被平均分给那些将收到他的礼物
的人.
然而,在任何一群朋友中,有些人将送出较多的礼物(可能是因为有较多的朋友),有些人有准备了较
多的钱.
给出一群朋友, 没有人的名字会长于 14 字符,给出每个人将花在送礼上的钱,和将收到他的礼物
的人的列表,
请确定每个人收到的比送出的钱多的数目.

## IMPORTANT NOTE

测试系统是 Linux 符合标准的 Unix 的协定.
用'\n'作为行的结束.
这和 Windows 系统用'\n' 和 '\r'作为行的结束是不同的.
你的程序不要被这困住了.


## INPUT FORMAT

第 1 行:人数 NP,2<= NP<=10  
第 2 到 NP+1 行:这 NP 个在组里人的名字 一个名字一行  
第 NP＋2 到最后:这里的 NP 段内容是这样组织的:  
第一行是将会送出礼物人的名字  
第二行包含二个数字: 第一个是原有的钱的数目（在 0 到 2000 的范围里）,第二个 NGi 是将收到这个送礼者礼物的人的个数 如果 NGi 是非零的, 在下面 NGi 行列出礼物的接受者的名字,一个名字一行.

## SAMPLE INPUT (file gift1.in)
```
5
dave
laura
owen
vick
amr
dave
200 3
laura
owen
vick
owen
500 1
dave
amr
150 2
vick
owen
laura 
0 2
amr
vick
vick
0 0
```

## OUTPUT FORMAT

输出 NP 行  
每行是一个的名字加上空格再加上收到的比送出的钱多的数目.  
对于每一个人,他名字的打印顺序应和他在输入的 2到 NP＋1行中输入的顺序相同.所有的送礼的钱都是整数.
每个人把相同数目的钱给每位要送礼的朋友,而且尽可能多给,不能给出的钱被送礼者自己保留.

## SAMPLE OUTPUT (file gift1.out)
```
dave 302
laura 66
owen -359
vick 141
amr -150
```
