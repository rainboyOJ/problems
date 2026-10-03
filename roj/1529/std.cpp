// std.cpp：ROJ 1529「欧拉回路」标准解
//
// 题面（见 content.md）：
//   无向图，输入包含若干组测试数据。每组第一行是两个正整数 N、M（1 < N < 1000），
//   随后 M 行每行给出一条边直接连接的两个节点编号（1..N）；N 为 0 时输入结束。
//   每组输出一行：存在欧拉回路输出 1，否则输出 0。
//
// 算法：Hierholzer 算法。
//   无向图存在欧拉回路 <=> 所有点度数都是偶数，且所有度数 > 0 的点连通。
//   先 O(N) 判断所有点度数是否为偶数；再从任意一个非孤立点出发，
//   用「显式栈 + 当前弧」迭代执行 Hierholzer，每走一条边就标记该边（两个方向的
//   半边一起标记），统计实际走过的边数。度数全偶时，走过的边数等于 M 当且仅当
//   所有边被同一条回路覆盖（即非孤立点连通），此时存在欧拉回路。
//   迭代写法避免 M 达到 498501（K999）时递归爆栈。
//
//   时间复杂度 O(N + M)，空间复杂度 O(N + M)。
//
// 本题答案唯一（0/1），所以输出按题面逐组给出即可，属于普通评测。
#include <cstdio>
#include <vector>

using namespace std;

// 读一个非负整数；到达文件末尾返回 -1
static int readInt()
{
    int c = getchar(), x = 0;
    while (c < '0' || c > '9')
    {
        if (c == EOF)
            return -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int main()
{
    // 邻接表：每条无向边 i 存成两个方向相反的半边 2i、2i+1，
    // 用 (边下标 >> 1) 还原成原边编号，标记一次即可同时去掉两个方向。
    vector<int> head, nxt, to; // head[v]：v 的第一条半边；nxt/to：链式前向星
    vector<int> deg;           // 度数
    vector<int> cur;           // 当前弧（Hierholzer 迭代用）
    vector<int> stk;           // 显式栈
    vector<char> used;         // 边是否已走过

    while (true)
    {
        int n = readInt();
        if (n <= 0) // 题面：N 为 0 时输入结束
            break;
        int m = readInt();

        head.assign(n + 1, -1);
        deg.assign(n + 1, 0);
        nxt.clear();
        to.clear();
        nxt.reserve(2 * m);
        to.reserve(2 * m);

        for (int i = 0; i < m; i++)
        {
            int u = readInt(), v = readInt();
            nxt.push_back(head[u]);
            to.push_back(v);
            head[u] = (int)nxt.size() - 1;

            nxt.push_back(head[v]);
            to.push_back(u);
            head[v] = (int)nxt.size() - 1;

            deg[u]++, deg[v]++; // 自环使该点度数 +2
        }

        bool ok = true;
        for (int v = 1; v <= n; v++)
            if (deg[v] & 1)
                ok = false; // 有奇点，直接不存在欧拉回路

        if (ok)
        {
            int start = 1;
            while (start <= n && deg[start] == 0)
                start++; // 找一个非孤立点作为起点

            if (start <= n)
            {
                used.assign(m, 0);
                cur = head; // 当前弧初始化为表头
                stk.clear();
                stk.push_back(start);

                int walk = 0;
                while (!stk.empty())
                {
                    int v = stk.back();
                    int &p = cur[v];
                    while (p != -1 && used[p >> 1]) // 跳过已走过的边
                        p = nxt[p];
                    if (p == -1) // 无边可走，回溯
                        stk.pop_back();
                    else
                    {
                        used[p >> 1] = 1;
                        walk++;
                        stk.push_back(to[p]);
                    }
                }

                if (walk != m) // 还有边没被走到：非孤立点不连通
                    ok = false;
            }
        }

        puts(ok ? "1" : "0");
    }
    return 0;
}
