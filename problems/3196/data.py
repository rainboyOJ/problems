#!/usr/bin/env python
from functools import reduce
from itertools import *
from cyaron import *

for I in range(1,11):
    io = IO(file_prefix="p", data_id=I) # test3.in, test3.out
    n = randint(10,10000)
    m = randint(n,min(n*(n-1)/2,50000))
    io.input_writeln(n,m) # 输出这条边，以u v w的形式
    graph = Graph.graph(n, m, weight_limit=1000) 
    io.input_writeln(graph.to_str(output=Edge.unweighted_edge)) # 输出无权图，以每条边u v一行的格式
    io.output_gen('../std')


