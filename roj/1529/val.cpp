// val.cpp：ROJ 1529「欧拉回路」输入数据校验器（testlib）
//
// 校验内容与 content.md 题面一致：
//   - 若干组测试数据，每组第一行 "N M"（1 < N < 1000，M 为正整数）；
//   - 随后 M 行，每行 "u v"，1 <= u, v <= N（无向边，允许重边与自环）；
//   - 单独一行 "0" 表示输入结束。
#include "testlib.h"

int main(int argc, char **argv)
{
    registerValidation(argc, argv);

    int cases = 0;
    while (true)
    {
        int n = inf.readInt(0, 999, "n");
        if (n == 0) // 终止行
        {
            inf.readEoln();
            break;
        }
        if (n < 2)
            inf.quit(_fail, "n must satisfy 1 < N < 1000");

        inf.readSpace();
        int m = inf.readInt(1, 500000, "m");
        inf.readEoln();

        for (int i = 1; i <= m; i++)
        {
            inf.readInt(1, n, "u");
            inf.readSpace();
            inf.readInt(1, n, "v");
            inf.readEoln();
        }

        cases++;
        if (cases > 1000)
            inf.quit(_fail, "too many test cases in one file");
    }

    inf.readEof();
    return 0;
}
