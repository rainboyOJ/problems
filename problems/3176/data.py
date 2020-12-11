#!/usr/bin/env python
from functools import reduce
from itertools import *
from cyaron import *

for I in range(1,11):
    io = IO(file_prefix="p", data_id=I) # test3.in, test3.out
    n = randint(1,30000)
    la = randint(-100000,1000)
    lb  = randint(la+1,100000)
    s = randint(la,lb)
    io.input_writeln(n,s)
    for i in range(0,n-1):
        t1 = randint(-100000,1000)
        t2  = randint(t1+1,100000)
        io.input_writeln(t1,t2) # 输出这条边，以u v w的形式
    io.input_writeln(la,lb) # 输出这条边，以u v w的形式
    io.output_gen('../std')


