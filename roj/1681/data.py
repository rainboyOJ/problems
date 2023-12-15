#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(1,11):
    _max = ati([1E5])
    n = randint(10,100000)
    _in = [ randint(-1000,_max[0]) for i in range(0,n)]
    io = IO(file_prefix="lsh", data_id=i) # test3.in, test3.out
    io.input_writeln(n)
    io.input_writeln(_in)
    io.output_gen("../std")
