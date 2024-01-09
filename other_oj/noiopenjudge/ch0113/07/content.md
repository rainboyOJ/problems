## 描述


上周末，M.A. Ya教授对古老的玛雅有了一个重大发现。从一个古老的节绳（玛雅人用于记事的工具）中，教授发现玛雅人使用了一个一年有365天的叫做Haab的历法。这个Haab历法拥有19个月，在开始的18个月，一个月有20天，月份的名字分别是pop, no, zip, zotz, tzec, xul, yoxkin, mol, chen, yax, zac, ceh, mac, kankin, muan, pax, koyab, cumhu。这些月份中的日期用0到19表示。Haab历的最后一个月叫做uayet，它只有5天，用0到4表示。玛雅人认为这个日期最少的月份是不吉利的，在这个月法庭不开庭，人们不从事交易，甚至没有人打扫屋中的地板。     因为宗教的原因，玛雅人还使用了另一个历法，在这个历法中年被称为Tzolkin(holly年)，一年被分成13个不同的时期，每个时期有20天，每一天用一个数字和一个单词相组合的形式来表示。使用的数字是1~13，使用的单词共有20个，它们分别是：imix, ik, akbal, kan, chicchan, cimi, manik, lamat, muluk, ok, chuen, eb, ben, ix, mem, cib, caban, eznab, canac, ahau。注意：年中的每一天都有着明确唯一的描述，比如，在一年的开始，日期如下描述： 1 imix, 2 ik, 3 akbal, 4 kan, 5 chicchan, 6 cimi, 7 manik, 8 lamat, 9 muluk, 10 ok, 11 chuen, 12 eb, 13 ben, 1 ix, 2 mem, 3 cib, 4 caban, 5 eznab, 6 canac, 7 ahau, ，8 imix, 9 ik, 10 akbal ……也就是说数字和单词各自独立循环使用。 Haab历和Tzolkin历中的年都用数字0，1，……表示，数字0表示世界的开始。所以第一天被表示成： Haab: 0. pop 0 Tzolkin: 1 imix 0 请帮助M.A. Ya教授写一个程序可以把Haab历转化成Tzolkin历。 

## 输入


Haab历中的数据由如下的方式表示： 日期. 月份 年数 输入中的第一行表示要转化的Haab历日期的数据量。下面的每一行表示一个日期，年数小于5000。

## 输出


Tzolkin历中的数据由如下的方式表示： 天数字 天名称 年数 第一行表示输出的日期数量。下面的每一行表示一个输入数据中对应的Tzolkin历中的日期。

## 样例输入


```
3
10. zac 0
0. pop 0
10. zac 1995

```


## 样例输出


```
3
3 chuen 0
1 imix 0
9 cimi 2801

```


## 来源


POJ 1008

