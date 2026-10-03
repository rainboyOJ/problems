// chk.cpp：ROJ 1529「欧拉回路」特殊评测器（testlib）
//
// 本题输出唯一（每组一行 0/1），评测器不直接逐字节比对答案文件，
// 而是重新读入输入、独立计算判定结果，再与选手输出逐行核对：
//   无向图存在欧拉回路 <=> 所有点度数为偶数，且所有度数 > 0 的点连通。
// 同时校验答案文件（.out）与独立计算的结果一致，防止测试数据错配。
//
// 用法：chk <input-file> <output-file> <answer-file>
#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

const int MAXN = 1000;

int deg[MAXN + 1];
int fa[MAXN + 1];

int findSet(int x)
{
    // 迭代 + 路径压缩，避免递归写法（fa[x] = findSet(x) 写错参数会导致无限递归）
    int root = x;
    while (fa[root] != root)
        root = fa[root];
    while (fa[x] != root)
    {
        int nxt = fa[x];
        fa[x] = root;
        x = nxt;
    }
    return root;
}

static string trimLine(const string &s)
{
    size_t b = 0, e = s.size();
    while (b < e && (s[b] == ' ' || s[b] == '\t' || s[b] == '\r' || s[b] == '\n'))
        b++;
    while (e > b && (s[e - 1] == ' ' || s[e - 1] == '\t' || s[e - 1] == '\r' || s[e - 1] == '\n'))
        e--;
    return s.substr(b, e - b);
}

int main(int argc, char **argv)
{
    registerTestlibCmd(argc, argv);

    // 1) 读入全部测试数据并独立计算每组的答案
    vector<int> expect;
    while (true)
    {
        int n = inf.readInt(0, 999, "n");
        if (n == 0) // 终止行
        {
            inf.readEoln();
            break;
        }
        inf.readSpace();
        int m = inf.readInt(1, 500000, "m");
        inf.readEoln();

        for (int i = 1; i <= n; i++)
            deg[i] = 0, fa[i] = i;

        for (int i = 1; i <= m; i++)
        {
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            inf.readEoln();
            deg[u]++, deg[v]++; // 自环使该点度数 +2
            fa[findSet(u)] = findSet(v);
        }

        bool even = true;
        for (int i = 1; i <= n; i++)
            if (deg[i] & 1)
                even = false;

        int root = -1;
        bool connected = true;
        for (int i = 1; i <= n; i++)
            if (deg[i] > 0)
            {
                if (root == -1)
                    root = findSet(i);
                else if (findSet(i) != root)
                    connected = false;
            }

        expect.push_back(even && connected ? 1 : 0);
    }
    inf.readEof();

    // 2) 答案文件必须与独立计算结果一致（否则是数据问题）
    for (size_t i = 0; i < expect.size(); i++)
    {
        if (ans.eof())
            quitf(_fail, "answer file has fewer lines than test cases (%d expected)",
                  (int)expect.size());
        string a = trimLine(ans.readLine());
        string e = to_string(expect[i]);
        if (a != e)
            quitf(_fail, "answer file mismatch at case %d: expected %s, found %s",
                  (int)i + 1, e.c_str(), a.c_str());
    }
    if (!ans.seekEof())
        quitf(_fail, "answer file has extra content after the last test case");

    // 3) 选手输出逐行核对
    for (size_t i = 0; i < expect.size(); i++)
    {
        if (ouf.eof())
            quitf(_wa, "output has fewer lines than test cases (%d expected)",
                  (int)expect.size());
        string p = trimLine(ouf.readLine());
        if (p != "0" && p != "1")
            quitf(_wa, "line %d must be 0 or 1, found \"%s\"", (int)i + 1, p.c_str());
        if (p != to_string(expect[i]))
            quitf(_wa, "wrong answer on line %d: expected %s, found %s",
                  (int)i + 1, to_string(expect[i]).c_str(), p.c_str());
    }
    if (!ouf.seekEof())
        quitf(_wa, "extra content after the last test case");

    quitf(_ok, "%d test case(s) accepted", (int)expect.size());
    return 0;
}
