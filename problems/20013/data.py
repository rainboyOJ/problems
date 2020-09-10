#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(6,7):
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out

    n = randint(10,100)
    v = randint(1,100)
    s = randint(1,50000)
    io.input_writeln(n,v,s);
    for k in range(0,n):
        io.input_writeln(randint(1,50000),randint(0,5000),randint(1,50000))
    io.output_gen("../std")
