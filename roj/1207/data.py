#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(0,10):
    io = IO(file_prefix="gcdmax", data_id=i) # test3.in, test3.out

    a = randint(1,100000000)
    b = randint(1,100000000)
    if i <= 5:
        a = randint(10,1000)
        b = randint(10,1000)
    io.input_write(a,b)
    io.output_gen("../std")

