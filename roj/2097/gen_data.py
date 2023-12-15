#!/usr/bin/env python
from functools import reduce
from itertools import chain
from random import randint
import os

# 读入所有的数据
# data = [ list(map(int,line.split())) for line in sys.stdin ]
for i in range(1,3+1):
    os.system('python data30.py > data/p{}.in'.format(i))
    os.system('./std < data/p{}.in > data/p{}.out'.format(i,i))

for i in range(4,10+1):
    os.system('python data.py > data/p{}.in'.format(i))
    os.system('./std < data/p{}.in > data/p{}.out'.format(i,i))
