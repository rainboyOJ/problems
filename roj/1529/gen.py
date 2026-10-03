#!/usr/bin/env python3
"""ROJ 1529「欧拉回路」测试数据生成器（可复现，固定随机种子）

用法：
    python3 gen.py        # 生成 data/tour1.in ~ tour38.in，
                          # 再用 std.cpp 编译出的程序生成 tour#.out，
                          # 并自验：std 幂等性 + Python 参考实现独立核对答案

题面（见 content.md）：
    - 无向图；若干组测试数据，每组第一行 "N M"（1 < N < 1000，M 为正整数），
      随后 M 行每行 "u v"（1..N）；单独一行 "0" 表示输入结束。
    - 每组输出一行：存在欧拉回路输出 1，否则输出 0。

判定标准（与 std.cpp / chk.cpp / 参考实现一致）：
    无向图存在欧拉回路 <=> 所有点度数都是偶数，且所有度数 > 0 的点连通。

测例设计（38 组，与 data.yml 的 subtasks / inputFile: 'tour#.in' 对齐）：
     1  样例（与题面样例逐字节一致）：三角形(1) + 链(0)
     2  有解：三角形 + 孤立点
     3  无解：链状（6 点一条链）
     4  有解：环状（7 点一个环）
     5  无解：两个不连通的三角形
     6  无解：星形 K1,5（叶子度数为奇）
     7  有解：完全图 K5（度数全为 4）
     8  无解：完全图 K6（度数全为 5）
     9  有解：重边图（每条边都出现两次）
    10  无解：三个自环互不连通（度数全偶但不连通）
    11  有解：环 + 自环
    12  无解：两点单边（最小无解）
    13  有解：两点重边（最小有解）
    14  有解：n=60 随机欧拉图
    15  无解：随机欧拉图加一条弦（出现两个奇点）
    16  有解：两个环共用一个顶点（蝴蝶结）
    17  无解：一个大环 + 一条悬空链（不连通且有奇点）
    18  有解：n=999 单个大环（稀疏最大规模）
    19  无解：n=999 链状（稀疏最大规模）
    20  有解：完全图 K999（498501 条边，最大规模）
    21  无解：完全图 K600（度数为奇）
    22  有解：完全二分图 K400,400（两侧度数均为偶）
    23  无解：完全二分图 K400,401（一侧度数为奇）
    24  有解：30×30 环面网格（4-正则）
    25  无解：30×30 开网格（边界点度数为奇）
    26  混合：5 组小数据，1/0 混排
    27  混合：4 组全无解
    28  混合：4 组全有解
    29  有解：n=998 随机稀疏欧拉图（约 2.2 万条边）
    30  无解：同上再加一条弦（出现两个奇点）
    31  无解：n=999 两个不连通的大环
    32  有解：环 + 大量自环与重边
    33  无解：n=999 三个不连通的大环
    34  无解：主体有环但 999 号点只有自环（度数全偶但不连通）
    35  混合：5 组中等规模
    36  混合：4 组中等规模（网格 / 随机图）
    37  混合：4 组中等规模（环 / 链 / 自环 / 完全二分图）
    38  混合：6 组小数据（含最小有解、最小无解）
"""

from __future__ import annotations

import random
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
DATA_DIR = HERE / "data"
NUM_CASES = 38


# --------------------------------------------------------------------------- #
# 图构造辅助函数
# --------------------------------------------------------------------------- #
def edges_path(n: int, offset: int = 0) -> list[tuple[int, int]]:
    """一条链：offset+1 - offset+2 - ... - offset+n。"""
    return [(offset + i, offset + i + 1) for i in range(1, n)]


def edges_cycle(n: int, offset: int = 0) -> list[tuple[int, int]]:
    """一个环（n >= 3）。"""
    return edges_path(n, offset) + [(offset + n, offset + 1)]


def edges_complete(n: int) -> list[tuple[int, int]]:
    """完全图 Kn。度数为 n-1，n 为奇数时才存在欧拉回路。"""
    return [(u, v) for u in range(1, n + 1) for v in range(u + 1, n + 1)]


def edges_bipartite(a: int, b: int) -> list[tuple[int, int]]:
    """完全二分图 Ka,b：左部 1..a，右部 a+1..a+b。"""
    return [(u, a + w) for u in range(1, a + 1) for w in range(1, b + 1)]


def edges_star(k: int) -> list[tuple[int, int]]:
    """星形 K1,k：1 号点为星心，k 个叶子度数为 1。"""
    return [(1, v) for v in range(2, k + 2)]


def edges_torus(rows: int, cols: int) -> list[tuple[int, int]]:
    """rows × cols 环面网格：每个点度数为 4（上下左右各一条，首尾相接）。"""
    def id(i: int, j: int) -> int:
        return i * cols + j + 1

    edges = []
    for i in range(rows):
        for j in range(cols):
            edges.append((id(i, j), id(i, (j + 1) % cols)))
            edges.append((id(i, j), id((i + 1) % rows, j)))
    return edges


def edges_grid_open(rows: int, cols: int) -> list[tuple[int, int]]:
    """rows × cols 开网格（不首尾相接）：边界点度数为 3，必有奇点。"""
    def id(i: int, j: int) -> int:
        return i * cols + j + 1

    edges = []
    for i in range(rows):
        for j in range(cols):
            if j + 1 < cols:
                edges.append((id(i, j), id(i, j + 1)))
            if i + 1 < rows:
                edges.append((id(i, j), id(i + 1, j)))
    return edges


def random_eulerian(n: int, seed: int, extra_pairs: int = 0) -> list[tuple[int, int]]:
    """随机欧拉图（n >= 3，固定种子可复现）。

    构造：一个顺序 Hamilton 环（保证连通）+ 一个随机顺序 Hamilton 环，
    每个点度数为 4，全为偶数；再按 extra_pairs 追加若干「成对重边」，
    每条重边使两端点度数各 +2，奇偶性保持不变。
    """
    rng = random.Random(seed)
    edges = edges_cycle(n)

    perm = list(range(1, n + 1))
    rng.shuffle(perm)
    for i in range(n):
        u, v = perm[i], perm[(i + 1) % n]
        edges.append((u, v))

    for _ in range(extra_pairs):
        u = rng.randint(1, n)
        v = rng.randint(1, n)
        if u == v:  # 不要随机自环，保持图更自然
            continue
        edges.append((u, v))
        edges.append((u, v))
    return edges


# --------------------------------------------------------------------------- #
# 38 组数据：编号 -> (说明, [(N, 边表), ...])，每组文件末尾写一行 0
# --------------------------------------------------------------------------- #
def build_cases() -> dict[int, tuple[str, list[tuple[int, list[tuple[int, int]]]]]]:
    mixed_26 = [
        (5, edges_cycle(5)),          # 1
        (5, edges_path(5)),           # 0
        (6, edges_cycle(3) + [(x + 3, y + 3) for (x, y) in edges_cycle(3)]),  # 0
        (7, edges_complete(7)),       # 1
        (8, edges_complete(8)),       # 0
    ]
    mixed_27 = [
        (4, edges_star(3)),           # 0
        (5, edges_path(5)),           # 0
        (6, edges_cycle(3) + [(x + 3, y + 3) for (x, y) in edges_cycle(3)]),  # 0
        (6, edges_complete(6)),       # 0
    ]
    mixed_28 = [
        (3, edges_complete(3)),       # 1
        (6, edges_cycle(6)),          # 1
        (7, edges_complete(7)),       # 1
        (10, edges_cycle(5) + [(1, 6)] + [(i, i + 1) for i in range(6, 10)]
         + [(10, 1)]),                # 1（蝴蝶结）
    ]
    mixed_35 = [
        (100, random_eulerian(100, 1529351, extra_pairs=50)),   # 1
        (100, edges_path(100)),                                 # 0
        (100, edges_cycle(50) + edges_cycle(50, 50)),            # 0（两个环）
        (99, edges_complete(99)),                               # 1（度数 98）
        (50, edges_cycle(50) + [(1, 3)]),                        # 0（两个奇点）
    ]
    mixed_36 = [
        (200, random_eulerian(200, 1529361, extra_pairs=200)),  # 1
        (200, random_eulerian(200, 1529362, extra_pairs=200) + [(1, 4)]),  # 0
        (200, edges_grid_open(10, 20)),                          # 0
        (200, edges_torus(10, 20)),                              # 1
    ]
    mixed_37 = [
        (300, edges_cycle(300)),                                 # 1
        (300, edges_path(300)),                                  # 0
        (300, [(i, i) for i in range(1, 101)]),                  # 0（自环互不连通）
        (300, edges_bipartite(150, 150)),                        # 1（度数 150）
    ]
    mixed_38 = [
        (3, edges_complete(3)),                                  # 1
        (3, edges_path(3)),                                      # 0
        (2, [(1, 2), (1, 2)]),                                   # 1
        (2, [(1, 2)]),                                           # 0
        (5, edges_cycle(5) + [(3, 3)]),                          # 1
        (4, edges_complete(4)),                                  # 0
    ]

    cases: dict[int, tuple[str, list[tuple[int, list[tuple[int, int]]]]]] = {
        1: ("样例：三角形(1) + 链(0)",
            [(3, [(1, 2), (1, 3), (2, 3)]), (3, [(1, 2), (2, 3)])]),
        2: ("有解：三角形 + 孤立点", [(4, edges_cycle(3))]),
        3: ("无解：链状 6 点", [(6, edges_path(6))]),
        4: ("有解：环状 7 点", [(7, edges_cycle(7))]),
        5: ("无解：两个不连通的三角形",
            [(6, edges_cycle(3) + [(x + 3, y + 3) for (x, y) in edges_cycle(3)])]),
        6: ("无解：星形 K1,5（叶子度数为奇）", [(6, edges_star(5))]),
        7: ("有解：完全图 K5", [(5, edges_complete(5))]),
        8: ("无解：完全图 K6", [(6, edges_complete(6))]),
        9: ("有解：重边图（每条边出现两次）",
            [(4, [(1, 2), (1, 2), (2, 3), (2, 3), (3, 4), (3, 4), (4, 1), (4, 1)])]),
        10: ("无解：三个自环互不连通（度数全偶）", [(3, [(1, 1), (2, 2), (3, 3)])]),
        11: ("有解：环 + 自环", [(5, edges_cycle(5) + [(3, 3)])]),
        12: ("无解：两点单边", [(2, [(1, 2)])]),
        13: ("有解：两点重边", [(2, [(1, 2), (1, 2)])]),
        14: ("有解：n=60 随机欧拉图", [(60, random_eulerian(60, 152914, extra_pairs=30))]),
        15: ("无解：随机欧拉图 + 一条弦（两个奇点）",
             [(60, random_eulerian(60, 152915, extra_pairs=30) + [(1, 3)])]),
        16: ("有解：两个环共用一个顶点（蝴蝶结）",
             [(40, edges_cycle(20) + [(1, 21)]
               + [(i, i + 1) for i in range(21, 40)] + [(40, 1)])]),
        17: ("无解：大环 + 悬空链（不连通且有奇点）",
             [(80, edges_cycle(70) + [(71, 72), (72, 73)])]),
        18: ("有解：n=999 单个大环（稀疏最大规模）", [(999, edges_cycle(999))]),
        19: ("无解：n=999 链状（稀疏最大规模）", [(999, edges_path(999))]),
        20: ("有解：完全图 K999（498501 条边，最大规模）", [(999, edges_complete(999))]),
        21: ("无解：完全图 K600（度数为奇）", [(600, edges_complete(600))]),
        22: ("有解：完全二分图 K400,400（两侧度数均为偶）", [(800, edges_bipartite(400, 400))]),
        23: ("无解：完全二分图 K400,401（左侧度数为奇）", [(801, edges_bipartite(400, 401))]),
        24: ("有解：30×30 环面网格（4-正则）", [(900, edges_torus(30, 30))]),
        25: ("无解：30×30 开网格（边界点度数为奇）", [(900, edges_grid_open(30, 30))]),
        26: ("混合：5 组小数据 1/0 混排", mixed_26),
        27: ("混合：4 组全无解", mixed_27),
        28: ("混合：4 组全有解", mixed_28),
        29: ("有解：n=998 随机稀疏欧拉图（约 2.2 万条边）",
             [(998, random_eulerian(998, 152929, extra_pairs=10000))]),
        30: ("无解：同上加一条弦（两个奇点）",
             [(998, random_eulerian(998, 152930, extra_pairs=10000) + [(10, 500)])]),
        31: ("无解：n=999 两个不连通的大环",
             [(999, edges_cycle(500) + edges_cycle(499, 500))]),
        32: ("有解：环 + 大量自环与重边",
             [(500, edges_cycle(500)
               + [(3 * i, 3 * i) for i in range(1, 101)]          # 100 个自环
               + [(k, k + 1) for k in range(1, 51)
                  for _ in range(2)])]),                          # 50 条边各重复一次
        33: ("无解：n=999 三个不连通的大环",
             [(999, edges_cycle(333) + edges_cycle(333, 333) + edges_cycle(333, 666))]),
        34: ("无解：主体有环但 999 号点只有自环（度数全偶）",
             [(999, edges_cycle(998) + [(999, 999), (999, 999)])]),
        35: ("混合：5 组中等规模", mixed_35),
        36: ("混合：4 组中等规模（网格 / 随机图）", mixed_36),
        37: ("混合：4 组中等规模（环 / 链 / 自环 / 完全二分图）", mixed_37),
        38: ("混合：6 组小数据（含最小有解、最小无解）", mixed_38),
    }
    assert len(cases) == NUM_CASES, "case 数量必须与 data.yml 的 subtasks 一致"
    return cases


# --------------------------------------------------------------------------- #
# 参考实现：与题面判定等价的独立答案计算（度数全偶 + 非孤立点连通）
# --------------------------------------------------------------------------- #
def reference_answer(n: int, edges: list[tuple[int, int]]) -> int:
    deg = [0] * (n + 1)
    fa = list(range(n + 1))

    def find(x: int) -> int:
        while fa[x] != x:
            fa[x] = fa[fa[x]]
            x = fa[x]
        return x

    for u, v in edges:
        deg[u] += 1
        deg[v] += 1
        fu, fv = find(u), find(v)
        if fu != fv:
            fa[fu] = fv

    if any(d % 2 for d in deg[1:]):
        return 0
    root = None
    for v in range(1, n + 1):
        if deg[v] > 0:
            if root is None:
                root = find(v)
            elif find(v) != root:
                return 0
    return 1  # 没有边（M=0）时按惯例视为存在


# --------------------------------------------------------------------------- #
# 生成与自验
# --------------------------------------------------------------------------- #
def write_input(path: Path, problems: list[tuple[int, list[tuple[int, int]]]]) -> None:
    lines: list[str] = []
    for n, edges in problems:
        lines.append("%d %d" % (n, len(edges)))
        lines.extend("%d %d" % (u, v) for u, v in edges)
    lines.append("0")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def build_std() -> Path:
    """把 std.cpp 编译成临时可执行文件，返回其路径。"""
    src = HERE / "std.cpp"
    fd, name = tempfile.mkstemp(prefix="roj1529_std_")
    import os
    os.close(fd)
    bin_path = Path(name)
    subprocess.run(
        ["g++", "-O2", "-std=c++17", "-o", str(bin_path), str(src)],
        check=True,
    )
    return bin_path


def main() -> int:
    DATA_DIR.mkdir(exist_ok=True)
    cases = build_cases()
    std_bin = build_std()
    total_in = total_out = 0
    try:
        for idx in range(1, NUM_CASES + 1):
            desc, problems = cases[idx]
            in_path = DATA_DIR / ("tour%d.in" % idx)
            out_path = DATA_DIR / ("tour%d.out" % idx)
            write_input(in_path, problems)

            # 用 std.cpp 生成 .out
            with in_path.open("rb") as fin, out_path.open("wb") as fout:
                subprocess.run([str(std_bin)], stdin=fin, stdout=fout, check=True)

            # 自验 1：std 幂等（重复运行逐字节一致）
            with in_path.open("rb") as fin:
                again = subprocess.run([str(std_bin)], stdin=fin,
                                       stdout=subprocess.PIPE, check=True).stdout
            if again != out_path.read_bytes():
                raise SystemExit("tour%d.out 不幂等" % idx)

            # 自验 2：Python 参考实现独立核对答案
            expect = [reference_answer(n, e) for n, e in problems]
            got = [int(x) for x in out_path.read_text(encoding="utf-8").split()]
            if got != expect:
                raise SystemExit("tour%d.out 与参考答案不一致：%s != %s"
                                 % (idx, got, expect))

            total_in += in_path.stat().st_size
            total_out += out_path.stat().st_size
            print("tour%-2d  组数=%d  答案=%s  in=%9d B  out=%3d B  %s"
                  % (idx, len(problems), "".join(map(str, expect)),
                     in_path.stat().st_size, out_path.stat().st_size, desc))
    finally:
        std_bin.unlink(missing_ok=True)

    print("done: %d 组数据，data/ 合计 in=%d B out=%d B"
          % (NUM_CASES, total_in, total_out))
    return 0


if __name__ == "__main__":
    sys.exit(main())
