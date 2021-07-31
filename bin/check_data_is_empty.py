# 查检是不是每个文件有data文件夹,都有数据
import os
import sys
path = os.path

pids = os.listdir("./problems")
for pid in pids:
    files = os.listdir(path.join("./problems",pid))
    if "data" not in files:
        print("have no data dir",pid)
        continue
        # sys.exit(1)
    datas = os.listdir(path.join("./problems",pid,"data"))
    if len(datas) == 0:
        print("data dir empty",pid)
        # sys.exit(1)
