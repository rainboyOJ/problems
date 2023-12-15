#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(1,11):
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out

    a = randint(1,100000)
    c = randint(20,500)
    b =[randint(5,c) for x in range(0,a)]
    io.input_writeln(a,c)
    io.input_writeln(b)
    io.output_gen("../std")
