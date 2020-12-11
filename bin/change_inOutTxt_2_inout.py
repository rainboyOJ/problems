#!/usr/bin/env python
from functools import reduce
from itertools import *
import os
import glob


a = glob.glob("data/*.txt")
for f in a:
    f1,b = os.path.splitext(f)
    if 'input' in f:
        os.system("mv {} {}.in".format(f,f1))
    elif 'output' in f:
        os.system("mv {} {}.out".format(f,f1))
    else:
        print('error: ',f)

    # print(f1)
    # num = re.search(r'\d+$',f1).group()

