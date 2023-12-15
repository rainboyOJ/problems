#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(1,11):
    io = IO(file_prefix="problem", data_id=i) # test3.in, test3.out

    a = randint(2,20)
    io.input_writeln(a)
    __in = [ choice("011") for i in range(0,a) ]
    io.input_writeln(__in)
    io.input_write(randint(2,9))
    io.output_gen("../std")
