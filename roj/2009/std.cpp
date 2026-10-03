/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 21:48
 * update_at: 2026-10-02 21:48
 */
// std.cpp：USACO 1.3.1 混合牛奶（roj 2009）标准解
// 贪心：奶农按单价升序排序，依次买空，直到凑够 N 升，总花费最小。
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXM = 5005;

int N, M; // N：每天需要的牛奶量（<=2e6）；M：奶农个数（<=5000）

struct Farmer
{
    int p; // 单价 Pi（<=1000）
    int a; // 一天能卖出的牛奶量 Ai（<=2e6）
};

Farmer f[MAXM];

// 贪心选择标准：单价低的奶农优先买
bool cmp_less(const Farmer &x, const Farmer &y)
{
    return x.p < y.p;
}

int main()
{
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++)
        scanf("%d %d", &f[i].p, &f[i].a);

    sort(f, f + M, cmp_less);

    long long need = N; // 还差多少升
    long long cost = 0; // 累计花费。最坏 2e6 * 1000 = 2e9，用 int64 累加避免溢出
    for (int i = 0; i < M && need > 0; i++)
    {
        long long take = need;
        if (take > f[i].a) take = f[i].a; // 最多买 a 升
        cost += take * f[i].p;
        need -= take;
    }

    // 题面保证奶农总产量足够，need 最终为 0；M=0、N=0 时 cost 为 0
    printf("%lld", cost);
    return 0;
}
