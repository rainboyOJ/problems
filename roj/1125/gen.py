#!/usr/bin/env python3
"""ROJ 1125「矩阵乘法」测试数据生成器（可复现，固定随机种子）。

用法：
    python3 gen.py        # 生成 data/problem1.in ~ problem10.in
                           # 并用 std.cpp 编译出的程序生成对应 .out

题面约束（见 content.md）：
    - 输入：第一行 n m k（均小于 100），随后 A 矩阵 n 行 m 列、B 矩阵 m 行 k 列；
    - 每个矩阵元素的绝对值不超过 1000（允许负数）；
    - 输出：C 矩阵 n 行，每行 k 个整数，整数之间以一个空格分开，没有取模。

测例设计（10 组，覆盖小 / 中 / 大与边界情形）：
    1  1x1x1            最小规模，元素取 ±1000 边界值
    2  2x3x4            极小规模，含负数与 0
    3  10x10x10         小规模
    4  20x35x25         中小规模
    5  30x40x50         中规模，元素非负
    6  50x30x40         中规模，m 较小
    7  60x65x55         中大规模
    8  99x1x99          退化：m = 1
    9  1x99x99          退化：n = 1
    10 99x99x99         最大规模，元素全取 ±1000 边界值（数值也最大）

    说明：题面把 n、m、k 限制在 < 100，最大规模也只有约 99^3 ≈ 10^6 次乘加，
    C++ 下远达不到 1s 时限，因此第 10 组按「约束上界 + 最大数值」设计，
    这是本题在合法输入下能构造出的最重数据。
"""

from __future__ import annotations

import random
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
DATA_DIR = HERE / "data"

# (n, m, k, 随机种子, 元素下界, 元素上界, 是否只取边界值)
CASES = [
    (1, 1, 1, 112501, -1000, 1000, True),
    (2, 3, 4, 112502, -1000, 1000, False),
    (10, 10, 10, 112503, -1000, 1000, False),
    (20, 35, 25, 112504, -1000, 1000, False),
    (30, 40, 50, 112505, 0, 1000, False),
    (50, 30, 40, 112506, -1000, 1000, False),
    (60, 65, 55, 112507, -1000, 1000, False),
    (99, 1, 99, 112508, -1000, 1000, False),
    (1, 99, 99, 112509, -1000, 1000, False),
    (99, 99, 99, 112510, -1000, 1000, True),
]


def rand_matrix(rng: random.Random, rows: int, cols: int,
                lo: int, hi: int, edge_only: bool) -> list[list[int]]:
    """生成一个 rows x cols 的矩阵；edge_only 时元素只取 lo 或 hi。"""
    if edge_only:
        return [[rng.choice((lo, hi)) for _ in range(cols)] for _ in range(rows)]
    return [[rng.randint(lo, hi) for _ in range(cols)] for _ in range(rows)]


def write_case(case_id: int, n: int, m: int, k: int, rng: random.Random,
               lo: int, hi: int, edge_only: bool) -> Path:
    a = rand_matrix(rng, n, m, lo, hi, edge_only)
    b = rand_matrix(rng, m, k, lo, hi, edge_only)

    lines = ["%d %d %d" % (n, m, k)]
    lines += [" ".join(str(x) for x in row) for row in a]
    lines += [" ".join(str(x) for x in row) for row in b]

    path = DATA_DIR / ("problem%d.in" % case_id)
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return path


def build_std() -> Path:
    """把 std.cpp 编译成临时可执行文件，返回其路径。"""
    src = HERE / "std.cpp"
    bin_path = Path(tempfile.mkstemp(prefix="roj1125_std_")[1])
    subprocess.run(
        ["g++", "-O2", "-std=c++17", "-o", str(bin_path), str(src)],
        check=True,
    )
    return bin_path


def main() -> int:
    DATA_DIR.mkdir(exist_ok=True)
    std_bin = build_std()
    try:
        for idx, (n, m, k, seed, lo, hi, edge_only) in enumerate(CASES, start=1):
            rng = random.Random(seed)
            in_path = write_case(idx, n, m, k, rng, lo, hi, edge_only)
            out_path = DATA_DIR / ("problem%d.out" % idx)
            with in_path.open("rb") as fin, out_path.open("wb") as fout:
                subprocess.run([str(std_bin)], stdin=fin, stdout=fout, check=True)
            print("problem%d: n=%d m=%d k=%d  in=%d bytes  out=%d bytes"
                  % (idx, n, m, k, in_path.stat().st_size, out_path.stat().st_size))
    finally:
        std_bin.unlink(missing_ok=True)
    print("done: 10 cases regenerated in %s" % DATA_DIR)
    return 0


if __name__ == "__main__":
    sys.exit(main())
