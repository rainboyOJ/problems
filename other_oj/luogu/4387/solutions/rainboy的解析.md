---
title: "rainboy的解析"
date: "2024-02-09 11:08"
update: "2023-02-09 11:08"
author: rainboy
home:  https://github.com/rainboylvx
top: true
---

## 解析


考点: 如何验证出栈序列是否正确呢?

例如:

```
pushed: 1 2 3 4
poped:  2 4 1 3
```
为什么不对呢?

1. 先将$1,2$入栈

$$
\def\arraystretch{2}
\begin{array}{|c|}
\hline
2 \\
\hline
1 \\
\hline
\end{array}
$$

然后发现`poped`的开头是$2$,此时栈的顶也是$2$,所以这时,要把栈顶弹出来.


然后入栈$3,4$,发现`poped: 4 1 3`,开头是$4$,所以要把栈顶$4$弹出

$$
\def\arraystretch{2}
\begin{array}{|c|}
\hline
4 \\
\hline
3 \\
\hline
1 \\
\hline
\end{array}
$$


此时的栈如下,`poped: 1 3`,所有的元素都入栈了,但是栈顶与`poped`的开头不一样,也就是无法出栈了,所以失败


$$
\def\arraystretch{2}
\begin{array}{|c|}
\hline
3 \\
\hline
1 \\
\hline
\end{array}
$$


总结:

1. 一边入栈,一边检查栈顶是否与poped的开头一样
2. 如果一样,就弹出栈顶
3. 不一样就一直入栈
4. 如果最后栈内还有元素,那就失败,否则成功

```cpp
<%- include("./rainboy.cpp") _%>
```




