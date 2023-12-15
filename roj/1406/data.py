#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(1,11):
    io = IO(file_prefix="problem", data_id=i) # test3.in, test3.out

    a = randint(10,5000)
    b = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    s = []
    for k in range(0,a):
        _in = [ choice(b) for i in range(0,randint(2,8))]
        s.append(''.join(_in))
    io.input_writeln(' '.join(s))
    io.input_writeln(choice(s))
    _in = [ choice(b) for i in range(0,randint(2,8))]
    io.input_write(''.join(_in))
    io.output_gen("../std")
