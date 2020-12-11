#!/usr/bin/env python
from cyaron import *

for i in range(1,11):
    n = randint(2,50);
    m = randint(2,50);
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out
    io.input_writeln(n,m)
    io.input_writeln(" ".join([str(randint(5,50)) for i in range(0,n+1)]))
    io.output_gen("../std")

