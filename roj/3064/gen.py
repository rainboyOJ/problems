#!/usr/bin/env python3
"""3064 数独2 数据生成器。

从随机完整终盘出发逐格挖空，每次挖空后用 DLX 计数确认「唯一解」，
否则回填该格；按难度给出不同线索数，生成多组测试用例。

用法：python3 gen.py [输出目录，默认 data/]
"""

import os
import random
import subprocess
import sys
import tempfile

N = 16
FULL = (1 << N) - 1
HERE = os.path.dirname(os.path.abspath(__file__))

# 题面样例（content.md），作为 1.in，验证与题面输入输出格式一致
SAMPLE = [
    "--A----C-----O-I",
    "-J--A-B-P-CGF-H-",
    "--D--F-I-E----P-",
    "-G-EL-H----M-J--",
    "----E----C--G---",
    "-I--K-GA-B---E-J",
    "D-GP--J-F----A--",
    "-E---C-B--DP--O-",
    "E--F-M--D--L-K-A",
    "-C--------O-I-L-",
    "H-P-C--F-A--B---",
    "---G-OD---J----H",
    "K---J----H-A-P-L",
    "--B--P--E--K--A-",
    "-H--B--K--FI-C--",
    "--F---C--D--H-N-",
]


def box_id(r, c):
    return (r // 4) * 4 + (c // 4)


# ---------------------------------------------------------------- DLX 计数
class DLX:
    """Algorithm X (Dancing Links)，列 = 格子 + 行字母 + 列字母 + 宫字母。"""

    def __init__(self, ncol):
        self.n = ncol
        # 列头环形链表：0 <-> 1 <-> ... <-> ncol <-> 0
        self.L = list(range(ncol + 1))
        self.R = list(range(ncol + 1))
        for i in range(1, ncol + 1):
            self.L[i] = i - 1
            self.R[i] = i + 1 if i < ncol else 0
        self.L[0] = ncol
        self.R[0] = 1 if ncol else 0
        self.U = list(range(ncol + 1))
        self.D = list(range(ncol + 1))
        self.C = list(range(ncol + 1))
        self.tag = [None] * (ncol + 1)
        self.size = ncol
        self.sz = [0] * (ncol + 1)  # 每列剩余行数，用于最小列优先（MRV）

    def add_row(self, cols, tag):
        nodes = []
        for c in cols:
            self.size += 1
            i = self.size
            self.tag.append(tag)
            self.C.append(c)
            self.U.append(self.U[c])
            self.D.append(c)
            self.D[self.U[c]] = i
            self.U[c] = i
            self.L.append(-1)  # 占位，行链建完后统一闭合
            self.R.append(-1)
            self.sz[c] += 1
            nodes.append(i)
        # 闭合成环：每个节点左指前驱、右指后继（首尾相连）
        m = len(nodes)
        for k, i in enumerate(nodes):
            self.L[i] = nodes[k - 1]
            self.R[i] = nodes[(k + 1) % m]
        return nodes[0]

    def cover(self, c):
        self.R[self.L[c]] = self.R[c]
        self.L[self.R[c]] = self.L[c]
        i = self.D[c]
        while i != c:
            j = self.R[i]
            while j != i:
                self.U[self.D[j]] = self.U[j]
                self.D[self.U[j]] = self.D[j]
                self.sz[self.C[j]] -= 1
                j = self.R[j]
            i = self.D[i]

    def uncover(self, c):
        i = self.U[c]
        while i != c:
            j = self.L[i]
            while j != i:
                self.D[self.U[j]] = j
                self.U[self.D[j]] = j
                self.sz[self.C[j]] += 1
                j = self.L[j]
            i = self.U[i]
        self.R[self.L[c]] = c
        self.L[self.R[c]] = c

    def pick_column(self):
        """剩余行数最少的列；无列返回 0。"""
        best = 0
        bestsz = None
        c = self.R[0]
        while c != 0:
            s = self.sz[c]
            if bestsz is None or s < bestsz:
                best, bestsz = c, s
                if s <= 1:
                    break
            c = self.R[c]
        return best


def count_solutions(board, limit=2, budget=2_000_000):
    """返回解的个数（上限 limit）；超出 budget 返回 None。"""
    # 列号从 1 开始：0 是头节点；1..256 格子，257..512 (行,字母)，513..768 (列,字母)，769..1024 (宫,字母)
    d = DLX(4 * 256)  # 列 1..1024，0 为头节点
    for i in range(256):
        r, c = divmod(i, 16)
        b = box_id(r, c)
        vals = [board[i]] if board[i] >= 0 else range(16)
        for v in vals:
            d.add_row([1 + i, 257 + r * 16 + v, 513 + c * 16 + v, 769 + b * 16 + v], (i, v))
    cnt = [0]
    nodes = [0]

    def search():
        if cnt[0] >= limit:
            return
        nodes[0] += 1
        if nodes[0] > budget:
            raise OverflowError
        c = d.pick_column()
        if c == 0:
            cnt[0] += 1
            return
        d.cover(c)
        i = d.D[c]
        while i != c:
            j = d.R[i]
            while j != i:
                d.cover(d.C[j])
                j = d.R[j]
            search()
            j = d.L[i]
            while j != i:
                d.uncover(d.C[j])
                j = d.L[j]
            if cnt[0] >= limit:
                break
            i = d.D[i]
        d.uncover(c)

    try:
        search()
    except OverflowError:
        return None
    return cnt[0]


# ------------------------------------------------------------ 终盘与挖空
def build_counter():
    """编译同目录的 check2.cpp（C++ DLX 解计数器），失败返回 None。"""
    global _COUNTER
    if _COUNTER is not None:
        return _COUNTER
    src = os.path.join(HERE, "check2.cpp")
    if not os.path.exists(src):
        _COUNTER = ""  # 记录已尝试过，避免重复编译
        return _COUNTER
    dst = os.path.join(tempfile.gettempdir(), "roj3064_check2")
    try:
        r = subprocess.run(["g++", "-O2", "-std=c++17", "-o", dst, src],
                           capture_output=True, timeout=120)
        _COUNTER = dst if r.returncode == 0 else ""
    except Exception:
        _COUNTER = ""
    return _COUNTER


_COUNTER = None


def count_uniq(board, budget=2_000_000, timeout=20):
    """解的个数（截断到 2）：优先用 C++ DLX，超时/无编译器时回退 Python DLX。

    返回 1（唯一解）、2（至少两解）、None（无法判定）。
    """
    exe = build_counter()
    if exe:
        try:
            r = subprocess.run([exe], input="\n".join(board_to_text(board)) + "\n",
                               capture_output=True, text=True, timeout=timeout)
            out = r.stdout.split()
            if r.returncode == 0 and out:
                return int(out[0])
        except subprocess.TimeoutExpired:
            return None
        except Exception:
            pass
    return count_solutions(board, 2, budget)


def gen_full(rng):
    """随机回溯生成一个合法完整终盘。"""
    board = [-1] * 256

    def fill(i):
        if i == 256:
            return True
        r, c = divmod(i, 16)
        used = 0
        for j in range(16):
            v = board[r * 16 + j]
            if v >= 0:
                used |= 1 << v
        for k in range(16):
            v = board[k * 16 + c]
            if v >= 0:
                used |= 1 << v
        br, bc = (r // 4) * 4, (c // 4) * 4
        for x in range(4):
            for y in range(4):
                v = board[(br + x) * 16 + bc + y]
                if v >= 0:
                    used |= 1 << v
        cand = [v for v in range(16) if not (used >> v) & 1]
        rng.shuffle(cand)
        for v in cand:
            board[i] = v
            if fill(i + 1):
                return True
        board[i] = -1
        return False

    if not fill(0):
        raise RuntimeError("生成完整终盘失败")
    return board


def carve(board, target, rng, budget, tries=1):
    """从终盘挖空到 target 条线索；每步保持唯一解，挖不动为止。

    单步唯一性是单调的（少一条线索只会解更多），所以唯一能改变结果的是
    移除顺序；tries>1 时跑多种顺序，取线索数最少的结果。
    """
    best_board, best_clues = None, 257
    for _ in range(tries):
        trial = board[:]
        order = list(range(256))
        rng.shuffle(order)
        clues = 256
        for i in order:
            if clues <= target:
                break
            saved = trial[i]
            trial[i] = -1
            if count_uniq(trial, budget) == 1:
                clues -= 1
            else:
                trial[i] = saved
        if clues < best_clues:
            best_board, best_clues = trial, clues
        if best_clues <= target:
            break
    board[:] = best_board
    return best_clues


def board_to_text(board):
    return ["".join("-" if board[i] < 0 else chr(65 + board[i]) for i in range(r * 16, r * 16 + 16)) for r in range(16)]


def build_case(seed, target, budget=2_000_000, tries=1):
    rng = random.Random(seed)
    board = gen_full(rng)
    clues = carve(board, target, rng, budget, tries)
    assert count_uniq(board, max(budget, 4_000_000)) == 1, f"seed={seed} 非唯一解"
    return board_to_text(board), clues


# 文件 -> 用例列表（seed, 目标线索数, 搜索预算, 顺序重试次数）
# 16x16 数独约束较松，单步挖空通常在 ~90 条线索处停滞（局部极小），故困难例用多次顺序重试。
PLAN = [
    ("1.in", None),                                   # 题面样例
    ("2.in", [(101, 150, 500_000, 1)]),               # 简单
    ("3.in", [(102, 135, 500_000, 1)]),               # 简单
    ("4.in", [(103, 110, 1_000_000, 4)]),             # 中等
    ("5.in", [(104, 95, 1_000_000, 4)]),              # 中等
    ("6.in", [(105, 88, 4_000_000, 16)]),             # 困难
    ("7.in", [(106, 88, 4_000_000, 16)]),             # 困难
    ("8.in", [(107, 120, 1_000_000, 1),               # 多组用例混合难度
              (108, 95, 1_000_000, 4),
              (109, 90, 4_000_000, 16)]),
]


def main():
    out_dir = sys.argv[1] if len(sys.argv) > 1 else os.path.join(HERE, "data")
    os.makedirs(out_dir, exist_ok=True)
    total_cases = 0
    for name, cases in PLAN:
        texts = []
        if cases is None:
            texts = [SAMPLE]
            print(f"{name}: 题面样例 (89 clues)")
        else:
            for seed, target, budget, tries in cases:
                grid, clues = build_case(seed, target, budget, tries)
                texts.append(grid)
                print(f"{name}: seed={seed} 目标={target} 重试={tries} 实际线索={clues}")
        with open(os.path.join(out_dir, name), "w") as f:
            f.write("\n\n".join("\n".join(t) for t in texts) + "\n")
        total_cases += len(texts)
    print(f"共 {len(PLAN)} 个 .in 文件，{total_cases} 组用例")


if __name__ == "__main__":
    main()
