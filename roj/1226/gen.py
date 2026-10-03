#!/usr/bin/env python3
"""ROJ 1226「装箱问题」测试数据生成器（可复现，固定随机种子）。

用法：
    python3 gen.py        # 重新生成 data/boxes*.in，并用 std.cpp 编译出的
                          # 程序生成对应 .out

题面（见 content.md）：
    - 每行订单为六个整数，分别是 1*1 ~ 6*6 六种产品的数量；
    - 输入以一行 6 个 0 结尾，该行不产生输出；
    - 每个订单输出一行：装满这些产品所需的最少 6*6 箱子数。

测例设计（9 组，文件名 boxes0 ~ boxes8，与 data.json 对齐）：
    boxes0  题面样例（原样复刻，含 6 个 0 结束行）
    boxes1  全 0 边界：输入只有结束行，输出为空
    boxes2  单种 6*6：0/1/7/100 件（每件独占一箱）
    boxes3  单种 1*1：1/36/37/72/73 件（36 格一箱的上下取整边界）
    boxes4  单种 2/3/4/5*5 各件的整箱边界
    boxes5  大件剩位填充边界：5*5 余 11 格、4*4 余 20 格、
            4*4+2*2、3*3+2*2、1*1 溢出等经典临界值
    boxes6  混合随机中等：30 个订单，数量 0 ~ 500
    boxes7  大数量：10 个订单，数量 0 ~ 20000（含纯 6*6 万件量级）
    boxes8  混合边界压测：50 个订单，围绕 36/9/4 的倍数与随机值混合
"""

from __future__ import annotations

import random
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
DATA_DIR = HERE / "data"

# (case 名, 订单行列表；写 .in 时末尾自动补 "0 0 0 0 0 0" 结束行)
CASES: list[tuple[str, list[str]]] = [
    # 1. 题面样例
    ("boxes0", [
        "0 0 4 0 0 1",
        "7 5 1 0 0 0",
    ]),
    # 2. 全 0：只有结束行，无输出
    ("boxes1", []),
    # 3. 单种 6*6
    ("boxes2", [
        "0 0 0 0 0 1",
        "0 0 0 0 0 7",
        "0 0 0 0 0 100",
    ]),
    # 4. 单种 1*1（36 格一箱）
    ("boxes3", [
        "1 0 0 0 0 0",
        "36 0 0 0 0 0",
        "37 0 0 0 0 0",
        "72 0 0 0 0 0",
        "73 0 0 0 0 0",
    ]),
    # 5. 单种 2*2 / 3*3 / 4*4 / 5*5 整箱边界
    ("boxes4", [
        "0 1 0 0 0 0",
        "0 9 0 0 0 0",
        "0 10 0 0 0 0",
        "0 0 1 0 0 0",
        "0 0 4 0 0 0",
        "0 0 5 0 0 0",
        "0 0 0 1 0 0",
        "0 0 0 2 0 0",
        "0 0 0 0 1 0",
        "0 0 0 0 3 0",
    ]),
    # 6. 大件剩位填充的经典临界值
    ("boxes5", [
        "11 0 0 0 1 0",   # 5*5 余 11 格正好塞满
        "12 0 0 0 1 0",   # 多 1 件 1*1 就要加一箱
        "20 0 0 1 0 0",   # 4*4 余 20 格正好塞满
        "21 0 0 1 0 0",
        "0 5 0 1 0 0",    # 4*4 余位恰好塞 5 件 2*2
        "0 6 0 1 0 0",
        "0 5 1 0 0 0",    # 1 件 3*3 的余位恰好塞 5 件 2*2
        "0 6 1 0 0 0",
        "0 9 4 0 0 0",    # 4 件 3*3 拼满一箱后，9 件 2*2 另开一箱
        "36 9 4 1 1 1",   # 六种各占一箱
        "0 0 0 1 1 1",    # 4*4/5*5/6*6 各占一箱
        "7 5 1 0 0 0",    # 题面样例 2：全部塞进一箱
    ]),
    # 7. 混合随机中等
    ("boxes6", []),
    # 8. 大数量
    ("boxes7", []),
    # 9. 混合边界压测
    ("boxes8", []),
]


def build_cases() -> list[tuple[str, list[str]]]:
    """为随机测例补全订单行，返回 (名称, 订单行) 完整列表。"""
    rng = random.Random(1226)
    cases = dict(CASES)

    # boxes6：30 个订单，数量 0 ~ 500
    cases["boxes6"] = [
        " ".join(str(rng.randint(0, 500)) for _ in range(6))
        for _ in range(30)
    ]

    # boxes7：10 个订单，数量 0 ~ 20000，首行为纯 6*6 万件量级
    lines = ["0 0 0 0 0 10000"]
    lines += [" ".join(str(rng.randint(0, 20000)) for _ in range(6))
              for _ in range(9)]
    cases["boxes7"] = lines

    # boxes8：50 个订单，围绕 36/9/4 的倍数与 ±1 临界值混合
    lines = []
    for i in range(50):
        if i % 5 == 0:
            # 某几种数量取倍数临界值，其余为 0
            base = [0, 0, 0, 0, 0, 0]
            kinds = rng.sample(range(6), rng.randint(1, 6))
            for k in kinds:
                unit = (36, 9, 4, 1, 1, 1)[k]
                base[k] = unit * rng.randint(0, 30) + rng.choice([0, 1])
            lines.append(" ".join(map(str, base)))
        elif i % 5 == 1:
            # 六种全有、量级悬殊
            lines.append("%d %d %d %d %d %d" % (
                rng.choice([0, 1, 35, 36, 37]),
                rng.choice([0, 8, 9, 10, 100]),
                rng.choice([0, 3, 4, 5, 50]),
                rng.choice([0, 1, 2, 40]),
                rng.choice([0, 1, 11, 20]),
                rng.choice([0, 1, 5, 500]),
            ))
        else:
            lines.append(" ".join(str(rng.randint(0, 3000)) for _ in range(6)))
    cases["boxes8"] = lines

    return [(name, cases[name]) for name, _ in CASES]


def build_std() -> Path:
    """把 std.cpp 编译成临时可执行文件，返回其路径。"""
    src = HERE / "std.cpp"
    fd, bin_path = tempfile.mkstemp(prefix="roj1226_std_")
    import os
    os.close(fd)
    subprocess.run(
        ["g++", "-O2", "-std=c++17", "-o", bin_path, str(src)],
        check=True,
    )
    return Path(bin_path)


def main() -> int:
    DATA_DIR.mkdir(exist_ok=True)
    std_bin = build_std()
    try:
        for name, orders in build_cases():
            text = "".join(line + "\n" for line in orders)
            text += "0 0 0 0 0 0\n"          # 输入以 6 个 0 结尾
            in_path = DATA_DIR / (name + ".in")
            in_path.write_text(text, encoding="utf-8")

            out_path = DATA_DIR / (name + ".out")
            with in_path.open("rb") as fin, out_path.open("wb") as fout:
                subprocess.run([str(std_bin)], stdin=fin, stdout=fout,
                               check=True)
            print("%s: orders=%d  in=%d bytes  out=%d bytes"
                  % (name, len(orders), in_path.stat().st_size,
                     out_path.stat().st_size))
    finally:
        std_bin.unlink(missing_ok=True)
    print("done: %d cases regenerated in %s" % (len(CASES), DATA_DIR))
    return 0


if __name__ == "__main__":
    sys.exit(main())
