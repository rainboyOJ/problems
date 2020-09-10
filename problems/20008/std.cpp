#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 10000;
int f[MAXN],  t[55];

int main()
{
    int T, n, cas, i, j, len, ma;
    T=1;
    for(cas = 1; cas <= T; cas++)
    {
        scanf("%d%d", &n, &len);
        len--;                         //留最后一秒开始唱金歌劲曲
        for(i = 1; i <= n; i++)
            scanf("%d", &t[i]);

        memset(f, 0, sizeof(f));
        ma = 0;         //记录最多歌曲数。
        for(i = 1; i <= n; i++)
        {
            for(j = len; j >= t[i]; j--)
            {
                if(f[j - t[i]] >= 1|| j == t[i])  //在j时间内可以唱完第i首歌。
                {
                    f[j] = max(f[j], f[j - t[i]] + 1);
                    ma = max(ma, f[j]);
                }
            }
        }
        for(i = len; f[i] != ma; i--);  //寻找唱最多歌情况下，时间最长的那个
        if(ma == 0)                             //在给定时间内无法唱完任何一首歌
            printf("%d %d\n",i,678);
        else
            printf("%d %d\n",1 + ma, i + 678);
    }
    return 0;
}
