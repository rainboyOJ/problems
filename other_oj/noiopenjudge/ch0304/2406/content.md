## 描述


Bessie is playing a card game with her N-1 (2 <= N <= 100) cow friends using a deck with K (N <= K <= 100,000; K is a multiple of N) cards.  The deck contains M = K/N "good" cards and K-M "bad" cards. Bessie is the dealer and, naturally, wants to deal herself all of the "good" cards. She loves winning.


Her friends suspect that she will cheat, though, so they devise a dealing system in an attempt to prevent Bessie from cheating. They tell her to deal as follows:   

1. Start by dealing the card on the top of the deck to the cow to her right
2. Every time she deals a card, she must place the next P (1 <= P <= 10) cards on the bottom of the deck; and   
3. Continue dealing in this manner to each player sequentially in a counterclockwise manner


Bessie, desperate to win, asks you to help her figure out where she should put the "good" cards so that she gets all of them. Notationally, the top card is card #1, next card is #2, and so on.

中文翻译:by rainboy

贝西正在和她的 N-1 (2 <= N <= 100) 个奶牛朋友玩纸牌游戏，她使用的是一副有 K (N <= K <= 100,000; K 是 N 的倍数) 张牌的纸牌。这副牌包含 M = K/N 张 "好牌 "和 K-M 张 "坏牌"。贝西是发牌员，她自然想把所有的 "好 "牌都发到自己手里。她喜欢赢。

但她的朋友们怀疑她会作弊，于是他们设计了一个发牌系统，试图阻止贝茜作弊。他们告诉她按以下方式发牌：

1. 首先，把牌堆顶的牌发给右边的那只牛。
2. 每次她发牌时，必须把接下来的下 P（1 <= P <= 10）张牌放在牌堆底部；以此类推。
3. 继续以逆时针的方式按顺序向每位玩家发牌。

贝西急于取胜，请您帮她想出应该把 "好 "牌放在哪里，这样她就能拿到所有的牌。按理说，最上面的牌是 1 号牌，下一张是 2 号牌，以此类推。

## 输入


* Line 1: Three space-separated integers: N, K, and P

- 第 1 行：三个空格分隔的整数：N、K 和 P

## 输出


* Lines 1..M: Positions from top in ascending order in which Bessie should place "good" cards, such that when dealt, Bessie will obtain all good cards.

- 第 1...M 行：从上往下依次排列贝西应该放 "好 "牌的位置，这样发牌时，贝西就能拿到所有的好牌。

## 样例输入


```
3 9 2
```


## 样例输出


```
3
7
8
```


## 提示


INPUT DETAILS: 输入细节：

Bessie is playing cards with two cow friends and a deck of 9 cards. She must place two cards on the bottom of the deck each time she deals one.

贝西正在和两个奶牛朋友玩扑克牌，她有一副 9 张牌。每次发牌时，她必须在牌的底部放两张牌。

OUTPUT DETAILS: 输出细节：

Bessie should put the "good" cards in positions 3, 7, and 8. The cards will be dealt as follows; the card numbers are "position in original deck":

贝西应该把 "好 "牌放在 3、7 和 8 的位置。发牌过程如下，牌号是 "在原牌中的位置"：

```
                                     Card Deck         P1      P2    Bessie
Initial configuration           1 2 3 4 5 6 7 8 9  - - -   - - -   - - -
Deal top card [1] to Player 1   2 3 4 5 6 7 8 9    1 - -   - - -   - - -
Top card to bottom (#1 of 2)    3 4 5 6 7 8 9 2    1 - -   - - -   - - -
Top card to bottom (#2 of 2)    4 5 6 7 8 9 2 3    1 - -   - - -   - - -
Deal top card [4] to Player 2   5 6 7 8 9 2 3      1 - -   4 - -   - - -
Top card to bottom (#1 of 2)    6 7 8 9 2 3 5      1 - -   4 - -   - - -
Top card to bottom (#2 of 2)    7 8 9 2 3 5 6      1 - -   4 - -   - - -
Deal top card [7] to Bessie     8 9 2 3 5 6        1 - -   4 - -   7 - -
Top card to bottom (#1 of 2)    9 2 3 5 6 8        1 - -   4 - -   7 - -
Top card to bottom (#2 of 2)    2 3 5 6 8 9        1 - -   4 - -   7 - -
Deal top card [2] to Player 1   3 5 6 8 9          1 2 -   4 - -   7 - -
Top card to bottom (#1 of 2)    5 6 8 9 3          1 2 -   4 - -   7 - -
Top card to bottom (#2 of 2)    6 8 9 3 5          1 2 -   4 - -   7 - -
Deal top card [6] to Player 2   8 9 3 5            1 2 -   4 6 -   7 - -
Top card to bottom (#1 of 2)    9 3 5 8            1 2 -   4 6 -   7 - -
Top card to bottom (#2 of 2)    3 5 8 9            1 2 -   4 6 -   7 - -
Deal top card [3] to Bessie     5 8 9              1 2 -   4 6 -   7 3 -
Top card to bottom (#1 of 2)    8 9 5              1 2 -   4 6 -   7 3 -
Top card to bottom (#2 of 2)    9 5 8              1 2 -   4 6 -   7 3 -
Deal top card [9] to Player 1   5 8                1 2 9   4 6 -   7 3 -
Top card to bottom (#1 of 2)    8 5                1 2 9   4 6 -   7 3 -
Top card to bottom (#2 of 2)    5 8                1 2 9   4 6 -   7 3 -
Deal top card [5] to Player 2   8                  1 2 9   4 6 5   7 3 -
Top card to bottom (#1 of 2)    8                  1 2 9   4 6 5   7 3 -
Top card to bottom (#1 of 2)    8                  1 2 9   4 6 5   7 3 -
Deal top card [8] to Bessie     -                  1 2 9   4 6 5   7 3 8
```

Bessie will end up with the "good cards" that have been placed in positions 3, 7, and 8 in the original deck.

贝西最终会拿到原牌组中放在 3、7 和 8 号位置的 "好牌"。


## 来源


USACO December 2007 Bronze

