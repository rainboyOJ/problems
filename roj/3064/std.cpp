// 3064 数独2：16x16 字母数独（A~P），多组测试用例
// 位掩码 DFS + 约束传播（裸唯一 / 隐性唯一）+ MRV 选点
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

static const int N = 16;
static const int FULL = 0xFFFF; // 16 位，对应字母 A~P

int g[N][N];                     // -1 表示空格，0..15 表示 A..P
int rM[N], cM[N], bM[N];         // 行 / 列 / 4x4 宫 已占用位掩码
int filled;                      // 已填格子数
vector<int> trail;               // 传播+搜索落子顺序，用于撤销

inline int boxId(int r, int c) { return (r >> 2) * 4 + (c >> 2); }
inline int cand(int r, int c) { return FULL & ~(rM[r] | cM[c] | bM[boxId(r, c)]); }

void place(int i, int v) {
    int r = i >> 4, c = i & 15, m = 1 << v;
    g[r][c] = v; rM[r] |= m; cM[c] |= m; bM[boxId(r, c)] |= m; filled++;
}
void undoOne(int i) {
    int r = i >> 4, c = i & 15, v = g[r][c];
    int m = ~(1 << v);
    g[r][c] = -1; rM[r] &= m; cM[c] &= m; bM[boxId(r, c)] &= m; filled--;
}
void undoTo(size_t top) {
    while (trail.size() > top) { undoOne(trail.back()); trail.pop_back(); }
}

// 约束传播：反复应用「裸唯一」（格子仅剩一个候选）与「隐性唯一」
// （某字母在行/列/宫中只剩一个可放位置），直到不能再推。
// 出现 0 候选或单位内无处可放时返回 false（矛盾）。
bool propagate() {
    bool changed = true;
    while (changed) {
        changed = false;
        // 裸唯一
        for (int i = 0; i < 256; i++) {
            int r = i >> 4, c = i & 15;
            if (g[r][c] != -1) continue;
            int cd = cand(r, c);
            if (cd == 0) return false;
            if ((cd & -cd) == cd) { // 仅剩 1 位
                place(i, __builtin_ctz(cd));
                trail.push_back(i);
                changed = true;
            }
        }
        if (filled == 256) return true;
        // 隐性唯一：行
        for (int r = 0; r < N; r++) {
            for (int v = 0; v < N; v++) {
                int m = 1 << v;
                if (rM[r] & m) continue;
                int pos = -1, cnt = 0;
                for (int c = 0; c < N; c++) {
                    if (g[r][c] != -1) continue;
                    if (cand(r, c) & m) { pos = r * 16 + c; cnt++; }
                }
                if (cnt == 0) return false;
                if (cnt == 1) { place(pos, v); trail.push_back(pos); changed = true; }
            }
        }
        // 隐性唯一：列
        for (int c = 0; c < N; c++) {
            for (int v = 0; v < N; v++) {
                int m = 1 << v;
                if (cM[c] & m) continue;
                int pos = -1, cnt = 0;
                for (int r = 0; r < N; r++) {
                    if (g[r][c] != -1) continue;
                    if (cand(r, c) & m) { pos = r * 16 + c; cnt++; }
                }
                if (cnt == 0) return false;
                if (cnt == 1) { place(pos, v); trail.push_back(pos); changed = true; }
            }
        }
        // 隐性唯一：4x4 宫
        for (int br = 0; br < 4; br++) {
            for (int bc = 0; bc < 4; bc++) {
                int b = br * 4 + bc;
                for (int v = 0; v < N; v++) {
                    int m = 1 << v;
                    if (bM[b] & m) continue;
                    int pos = -1, cnt = 0;
                    for (int x = 0; x < 4; x++) {
                        for (int y = 0; y < 4; y++) {
                            int r = br * 4 + x, c = bc * 4 + y;
                            if (g[r][c] != -1) continue;
                            if (cand(r, c) & m) { pos = r * 16 + c; cnt++; }
                        }
                    }
                    if (cnt == 0) return false;
                    if (cnt == 1) { place(pos, v); trail.push_back(pos); changed = true; }
                }
            }
        }
    }
    return true;
}

bool dfs() {
    if (!propagate()) return false;
    if (filled == 256) return true;
    // MRV：选候选最少的空格
    int br = -1, bc = -1, best = N + 1, bcand = 0;
    for (int i = 0; i < 256; i++) {
        int r = i >> 4, c = i & 15;
        if (g[r][c] != -1) continue;
        int cd = cand(r, c);
        int pc = __builtin_popcount(cd);
        if (pc < best) { best = pc; bcand = cd; br = r; bc = c; if (pc == 1) break; }
    }
    size_t top = trail.size();
    for (int t = bcand; t; t &= t - 1) {
        int v = __builtin_ctz(t); // 从最小字母开始尝试
        place(br * 16 + bc, v);
        trail.push_back(br * 16 + bc);
        if (dfs()) return true;
        undoTo(top);
    }
    return false;
}

// 读入一个 16x16 棋盘；字符非法或与已有冲突返回 false
bool readBoard(vector<string> &lines) {
    for (int i = 0; i < N; i++) rM[i] = cM[i] = bM[i] = 0;
    filled = 0; trail.clear();
    for (int i = 0; i < N; i++) {
        const string &s = lines[i];
        if ((int)s.size() != N) return false;
        for (int j = 0; j < N; j++) {
            char ch = s[j];
            if (ch == '-') continue; // 空格保持 g=-1（初始化见下）
            if (ch < 'A' || ch > 'P') return false;
            int v = ch - 'A', m = 1 << v, b = boxId(i, j);
            if ((rM[i] | cM[j] | bM[b]) & m) return false; // 已有冲突
            rM[i] |= m; cM[j] |= m; bM[b] |= m;
            g[i][j] = v; filled++;
        }
    }
    return true;
}

int main() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue; // 用例之间的空行
        lines.push_back(line);
        if ((int)lines.size() == N) {
            // 先把所有格子清空，再填入题面给定字母
            for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) g[i][j] = -1;
            if (readBoard(lines)) {
                dfs();
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) putchar('A' + g[i][j]);
                    putchar('\n');
                }
                putchar('\n'); // 每组输出后一个空行
            }
            lines.clear();
        }
    }
    return 0;
}
