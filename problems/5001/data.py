#!/usr/bin/env python
from cyaron import *

#=== 字符串
# s1 = String.random(5) # 生成一个5个字母的单词，从小写字母中随机选择
# s1 = String.random((10, 20), charset="abcd1234") # 生成一个10到20个字母之间的单词，从abcd1234共8个字符中随机选择
# s1 = String.random(10, charset="#######...") # 生成一个10个字母的只有'#'和'.'组成的字符串，'#'的可能性是70%，'.'可能30%。
# s1 = String.random_sentence((10, 20), word_separators=",;", sentence_terminators=None, first_letter_uppercase=False, word_length_range=(2, 10), charset="abcdefg") # 生成一个10到20个单词的句子，以逗号或分号随机分割，第一个单词首字母不大写，结尾没有任何符号，每个单词2到10字母长，从abcdefg共7个字符中随机选择
# 以上所有参数，对于以下所有指令也有效

for i in range(1,11):
    n = randint(2,50);
    io = IO(file_prefix="p", data_id=i) # test3.in, test3.out
    io.input_writeln(n)
    for _ in range(0,n):
        s = String.random(randint(2,30),charset="01")
        print(s)
        io.input_writeln(s)
    # io.output_gen("../std")

