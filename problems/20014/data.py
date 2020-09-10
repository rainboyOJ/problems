#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(4,11):
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out

    n = randint(10,100)
    io.input_writeln(n)
    a = []
    while 1:
        s =  randint(-100000,100000)
        if s in a:
            continue
        a.append(s)
        if len(a) == n:
            break
    a.sort()
    io.input_writeln(a)
    b = []
    for k in range(0,n):
        b.append( randint(10,100000))
    io.input_writeln(b)
    io.output_gen("../std")
