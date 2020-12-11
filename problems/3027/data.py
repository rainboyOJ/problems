#!/usr/bin/env python

from cyaron import * 

for i in range(1,11):
    n = randint(1,10000)
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out
    io.input_writeln(n)
    for j in range(0,n):
        io.input_writeln(randint(-10000,10000),randint(-10000,10000))
    io.output_gen('../std')
