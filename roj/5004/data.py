#!/usr/bin/env python
from functools import reduce
from itertools import *
from random import randint

#!/usr/bin/env python
from cyaron import *

#=== 字符串
# s1 = String.random(5) # 生成一个5个字母的单词，从小写字母中随机选择
# s1 = String.random((10, 20), charset="abcd1234") # 生成一个10到20个字母之间的单词，从abcd1234共8个字符中随机选择
# s1 = String.random(10, charset="#######...") # 生成一个10个字母的只有'#'和'.'组成的字符串，'#'的可能性是70%，'.'可能30%。
# s1 = String.random_sentence((10, 20), word_separators=",;", sentence_terminators=None, first_letter_uppercase=False, word_length_range=(2, 10), charset="abcdefg") # 生成一个10到20个单词的句子，以逗号或分号随机分割，第一个单词首字母不大写，结尾没有任何符号，每个单词2到10字母长，从abcdefg共7个字符中随机选择
# 以上所有参数，对于以下所有指令也有效

# for i in range(1,11):
    # n = randint(2,50);
    # io.input_writeln(n)
    # for _ in range(0,n):
        # s = String.random(randint(2,30),charset="01")
        # print(s)
        # io.input_writeln(s)
    # # io.output_gen("../std")




def iter2str(iter):
    return " ".join(map(str,iter))

for i in range(1,11):
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out
    n = randint(5,100000)
    m = randint(5,300)
    # print(n,m)
    io.input_writeln(n,m)
    io.input_writeln(iter2str([randint(1,100) for i in range(0,n)]))
    # print(iter2str([randint(1,9) for i in range(0,n)]))
    # print(" ".join(["0"]*n))
    for i in range(0,m):
        o = randint(1,2)
        if o == 1:
            x = randint(1,n)
            y = randint(x,n)
            z = randint(1,100)
            # print(o,x,y,z)
            io.input_writeln(o,x,y,z)
        else:
            x = randint(1,n)
            y = randint(x,n)
            io.input_writeln(o,x,y)
            # print(o,x,y)
    io.output_gen("../std")
