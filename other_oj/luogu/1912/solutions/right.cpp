#include <iostream>
#include <cstring>

using namespace std;

typedef long double LL;

const int N = 100010;

int n, l, p;
char str[N][35]; //记录所有诗句
LL f[N]; //设 f[i] 表示对前 i 句诗排版的最小不协调度
int g[N]; //设 g[i] 表示 f[i] 是从哪个决策转移过来的
int last[N]; //设 last[i] 表示第 i 句诗的末尾是第几个短句
LL s[N]; //设 s[i] 表示前 i 句诗的长度总和

struct Queue
{
    int x, l, r; //队列中存储三元组 (x, l, r)，x 表示决策点，[l ~ r] 目前的决策都是 x
}q[N]; //队列

int get(int i, int l, int r) //在队列中二分查找出 f[i] 使用的最优决策
{
    int pos; //记录 i 在队列中所在的区间的下标
    while(l <= r)
    {
        int mid = l + r >> 1;
        if(q[mid].l <= i && q[mid].r >= i) //如果 i 被 q[mid] 包含，说明找到 i 所在的区间
        {
            pos = mid;
            break;
        }
        //否则继续二分查找
        if(i < q[mid].l) r = mid - 1;
        else l = mid + 1;
    }
    return q[pos].x; //返回 f[i] 对应的最优决策
}

LL val(int j, int i) //计算从 f[j] 转移得到的 f[i]
{
    LL sum = abs(s[i] - s[j] + i - j - 1 - l);
    LL res = 1; //res = |sum[i] - sum[j] + i - j - 1 - l|^P
    for(int i = 1; i <= p; i++) res *= sum;
    return f[j] + res; //状态转移方程
}

void insert(int i, int &hh, int &tt) //将新决策 i 插入队列
{
    int pos = -1; //记录从哪插入新决策 i
    while(hh <= tt)
    {
        //如果新决策 i 比 q[tt].l 的决策更优，说明 q[tt].l 及以后应该用决策 i，更新决策 i 插入的位置，并删除 q[tt]
        if(val(i, q[tt].l) <= val(q[tt].x, q[tt].l)) pos = q[tt--].l;
        else
        {
            /*
            到这说明 q[tt].l 的决策比新决策 i 更优，如果新决策 i 比 q[tt].r 的决策更优，说明 i 插入的位置在
            q[tt].l ~ q[tt].r 之间，需要二分查找出一个固定的点 pos，使得 pos 之前的所有决策都比 i 更优，pos 
            之后的所有决策都比 i 更差，此时 pos 就是最终决策 i 插入的位置。否则说明 q[tt].r 的决策比 i 更优，
            那么此时 i 只能插入在 q[tt] 后面，而 pos 当前记录的位置就是 q[tt].r + 1，因此直接将 i 插入 pos 即可。
            */
            if(val(i, q[tt].r) < val(q[tt].x, q[tt].r))
            {
                //二分查找 i 应该插入的位置
                int l = q[tt].l, r = q[tt].r;
                while(l < r)
                {
                    int mid = l + r >> 1;
                    if(val(i, mid) <= val(q[tt].x, mid)) r = mid;
                    else l = mid + 1;
                }
                //二分查找得出 i 应该插入 r，则决策 q[tt].x 的区间缩小为 [q[tt].l ~ r - 1]
                q[tt].r = r - 1;
                pos = r;
            }
            //到这不管什么情况，此时 pos 都是 i 应该插入的位置，跳出循环
            break;
        }
    }
    //如果 pos != -1，说明找到一个位置，使得这个位置及以后的决策用 i 会更优，需要更新队列，
    //否则说明 i 放在哪都不是最优的，不用更新
    if(pos != -1) q[++tt] = {i, pos, n};
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &l, &p);

        for(int i = 1; i <= n; i++)
        {
            scanf("%s", str[i]);
            s[i] = s[i - 1] + strlen(str[i]); //预处理前缀和
        }

        int hh = 0, tt = 0;
        q[0] = {0, 1, n}; //0 也是一种方案，因此最开始所有状态的决策都是 0
        for(int i = 1; i <= n; i++)
        {
            int j = get(i, hh, tt); //在队列中二分查找出 f[i] 使用的最优决策
            f[i] = val(j, i); //更新状态
            g[i] = j; //记录当前状态是从哪个决策转移过来的

            while(hh <= tt && q[hh].r <= i) hh++; //删除无用决策
            q[hh].l = i + 1;

            insert(i, hh, tt); //将新决策 i 插入队列
        }

        if(f[n] > 1e18) puts("Too hard to arrange"); //无解
        else
        {
            printf("%lld\n", (long long)f[n]);

            for(int i = n; i >= 1; i = g[i]) last[g[i] + 1] = i; //预处理 last[]
            for(int i = 1; i <= n; i = last[i] + 1) //输出方案
            {
                for(int j = i; j <= last[i]; j++)
                {
                    printf("%s", str[j]);
                    if(j != last[i]) printf(" ");
                }
                puts("");
            }
        }
        printf("--------------------");
        if(T) puts("");
    }
    return 0;
}
