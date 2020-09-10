#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(1,11):
    io = IO(file_prefix="problem", data_id=i) # test3.in, test3.out

    a = randint(1,1000)
    b = randint(1,1000)
    io.input_writeln(a,b)
    for i in range(0,a):
        __in = [ randint(1,100000000) for x in range(0,b)]
        io.input_writeln(__in)
    io.output_gen("../std")
