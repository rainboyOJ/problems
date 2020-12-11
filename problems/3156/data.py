#!/usr/bin/env python
from functools import reduce
from itertools import *
from cyaron import *

for I in range(1,11):
    io = IO(file_prefix="p", data_id=I) # test3.in, test3.out
    n = randint(5,25000)
    m = randint(5,1000000)
    io.input_writeln(n,m)
    for i in range(0,n):
        a = randint(1,100000-10)
        b = randint(a+1,100000)
        io.input_writeln(a,b) # 输出这条边，以u v w的形式
    io.output_gen('../std')


