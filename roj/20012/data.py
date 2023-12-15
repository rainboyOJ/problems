#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(4,11):
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out

    n = randint(10,50)
    p = randint(1,n)
    io.input_writeln(n,p)
    a = []
    while 1:
        s =  randint(1,1000)
        if s in a:
            continue
        a.append(s)
        if len(a) == n:
            break
    a.sort()
    for k in range(0,n):
        io.input_writeln(a[k],randint(10,100))
    io.output_gen("../std")
