#!/usr/bin/env python
from functools import reduce
from itertools import *
from cyaron import *

for I in range(1,11):
    io = IO(file_prefix="p", data_id=I) # test3.in, test3.out
    L = randint(1,5)
    for i in range(0,L):
        n = randint(5,100)
        io.input_writeln(n) # 输出这条边，以u v w的形式
        for j in range(0,n):
            io.input_write(randint(1,1000)) # 输出这条边，以u v w的形式
        io.input_writeln() # 输出这条边，以u v w的形式
    io.output_gen('../std')


