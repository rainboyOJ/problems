#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(6,11):
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out

    a = randint(300,1000)
    b =[randint(5,100) for x in range(0,a)]
    io.input_writeln(a)
    io.input_writeln(b)
    io.output_gen("../std")
