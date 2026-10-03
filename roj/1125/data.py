#!/usr/bin/env python3
"""ROJ 1125「矩阵乘法」数据生成入口（保留 data.py 这个历史文件名）。

原 CYaRon 版脚本有两处与题面（content.md）不符：
  1. 规模用了 randint(1, 100)，会出现 100，而题面要求 n、m、k 均小于 100；
  2. 元素只取 randint(0, 1000)，而题面允许绝对值不超过 1000 的负数。

现在统一委托给 gen.py：固定随机种子、可复现，10 组数据覆盖小 / 中 / 大
与边界情形（m=1、n=1、全 ±1000），并顺带用 std.cpp 生成 .out。
"""

import subprocess
import sys
from pathlib import Path

GEN = Path(__file__).resolve().with_name("gen.py")

if __name__ == "__main__":
    sys.exit(subprocess.run([sys.executable, str(GEN)] + sys.argv[1:]).returncode)
