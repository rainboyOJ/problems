#!/usr/bin/env python
from functools import reduce
from itertools import *
from cyaron import *

for I in range(1,11):
    io = IO(file_prefix="p", data_id=I) # test3.in, test3.out
    n = randint(1,100)
    t = randint(-10000,10000)
    io.input_writeln(n,t)
    for i in range(0,n):
        io.input_writeln(randint(1,100)) # 输出这条边，以u v w的形式
    io.output_gen('../std')


