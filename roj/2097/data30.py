#!/usr/bin/env python
from functools import reduce
from itertools import *
from random import randint

# 读入所有的数据
# data = [ list(map(int,line.split())) for line in sys.stdin ]

n = 4
m = randint(1,5)
mod = randint(3,9)

print(n,m,mod)
print(" ".join([str(randint(1,10)) for _ in range(0,n)]))
for _ in range(0,m):
    o = randint(1,2)
    if o!=2:
        x = randint(1,n)
        y = randint(x,n)
        z = randint(1,10)
        print(o,x,y,z)
    else:
        x = randint(1,n)
        y = randint(x,n)
        print(o,x,y)

