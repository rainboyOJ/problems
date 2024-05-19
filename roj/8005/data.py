#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库

for i in range(1,11):
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out

    a = randint(1,1000000)
    if i == 1:
        a= 3
    if i == 2:
        a= 5
    if i == 3:
        a= 10
    if i > 3 and i <= 6:
        a= randint(50,1000)
    if i > 6 and i <= 10:
        a= randint(10000,100000)

    io.input_write(a)
    io.output_gen("../std.out")
