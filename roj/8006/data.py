#!/usr/bin/env python

from cyaron import * # 引入CYaRon的库
import random

def decimal_to_base(num, base):
    convert_string = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    result = ""
    while num > 0:
        # print(num % base)
        result = convert_string[num % base] + result
        num = num // base
    return result or "0"


for i in range(1,11):
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out
    if i <= 3:
        n = randint(5,10)
        io.input_writeln(n)
        for _ in range(n):
            a = random.choice([2,10])
            b = 12 - a
            num = random.randint(1,1000000)
            io.input_writeln(decimal_to_base(num, a),a,b)
            io.output_writeln(decimal_to_base(num, b))
    if i > 3 and i <= 6:
        n = randint(50,100)
        io.input_writeln(n)
        for _ in range(n):
            a = random.choice([2,10,16,8])
            b = random.choice([2,10,16,8])
            while b == a:
                b = random.choice([2,10,16,8])
            num = random.randint(500000,(1<<63)-1)
            io.input_writeln(decimal_to_base(num, a),a,b)
            io.output_writeln(decimal_to_base(num, b))
    if i > 6 and i <= 10:
        # n = randint(100000,100000)
        n = 10000
        io.input_writeln(n)
        for _ in range(n):
            a = randint(3,36)
            b = randint(3,36)
            while b == a:
                b = randint(3,36)
            num = random.randint(500000,(1<<63)-1)
            # print(num,a,b)
            io.input_writeln(decimal_to_base(num, a),a,b)
            io.output_writeln(decimal_to_base(num, b))

    # io.output_gen("../std.out")
