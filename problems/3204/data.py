#!/usr/bin/env python
from functools import reduce
from itertools import *
from cyaron import *

for I in range(1,11):
    io = IO(file_prefix="p", data_id=I) # test3.in, test3.out
    n = randint(5,50)
    m = randint(5,50)
    io.input_writeln(n,m) # 输出这条边，以u v w的形式
    for i in range(0,n):
        s = String.random(m, charset=".....***") # 生成一个10个字母的只有'#'和'.'组成的字符串，'#'
        io.input_writeln(s) # 输出这条边，以u v w的形式
    io.output_gen('../std')


