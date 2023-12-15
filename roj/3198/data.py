#!/usr/bin/env python
from functools import reduce
from itertools import *
from cyaron import *

for I in range(1,11):
    io = IO(file_prefix="p", data_id=I) # test3.in, test3.out
    L = randint(1,5)
    io.input_writeln(L)
    for i in range(0,L):
        n = randint(5,100)
        m = randint(n,min(n*(n-1)/2,200000))
        s = randint(0,n-1)
        t = randint(0,n-1)
        q = randint(10,100000000)
        io.input_writeln(n,m,s,t,q) # 输出这条边，以u v w的形式
        graph = Graph.graph(n, m, weight_limit=1000) 
        for edge in graph.iterate_edges(): # 遍历所有边，其中edge内保存的也是Edge对象
            io.input_writeln(edge.start-1,edge.end-1,edge.weight) # 输出这条边，以u v w的形式
    io.output_gen('../std')


