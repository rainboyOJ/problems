#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(1,11):
    io = IO(file_prefix="problem", data_id=i) # test3.in, test3.out

    s = "ABCDEFJHIGKLMNOPQRSTUVWXYZ"
    ss = []
    for k in range(0,16):
        x = choice(s)
        while x in ss:
            x = choice(s)
        ss.append(x)
    x1 = randint(0,14)
    x2 = randint(x1,15)
    ss[x1] = ss[x2]
    io.input_write(''.join(ss))
    io.output_gen("../std")
