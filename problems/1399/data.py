#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(1,11):
    io = IO(file_prefix="problem", data_id=i) # test3.in, test3.out

    a = randint(1,200)
    io.input_writeln(a)
    b = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for k in range(0,a):
        name = [choice(b) for x in range(0,randint(2,8))]
        name = ''.join(name)
        f = str(randint(20,100)) + '.'+str(randint(20,99))
        io.input_writeln(name,f,randint(0,1))
    io.output_gen("../std")
