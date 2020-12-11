# 得到下一个没有被占用的编号
import os
import sys
from os import path
listdir = sorted(list(map(int, filter(lambda x : x.isnumeric,os.listdir("./problems")))))
start=1000
if len(sys.argv) > 1:
    print("start=",sys.argv[1])
    start = int(sys.argv[1])

if listdir[0] != 1000 and start != 1000:
    print("1000")
    print(listdir[:10])
    sys.exit(0)

for idx,val in enumerate(listdir):
    if idx==0:
        continue
    if val <= start:
        continue;
    if val != listdir[idx-1]+1:
        print(listdir[idx-1]+1)
        print(listdir[idx-1:idx-1+10])
        sys.exit(0)
    
