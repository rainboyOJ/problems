#!/usr/bin/env python
from functools import reduce
from itertools import *
from random import randint

# 读入所有的数据
# data = [ list(map(int,line.split())) for line in sys.stdin ]

n = 100000
m = 100000
mod = randint(1000-1,571373)

print(n,m,mod)
print(" ".join([str(randint(1,100000)) for _ in range(0,n)]))
for _ in range(0,m):
    o = randint(1,2)
    if o!=2:
        x = randint(1,n)
        y = randint(x,n)
        z = randint(1,100000)
        print(o,x,y,z)
    else:
        x = randint(1,n)
        y = randint(x,n)
        print(o,x,y)

