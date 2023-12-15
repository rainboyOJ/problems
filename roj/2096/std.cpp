/*
TASK:cowxor
LANG:C++
*/
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 100005;

int a[MAXN], b[MAXN], ans, st, ed, n;
int ch[MAXN * 10][2], node;

void insert(int num)
{
    int u = 0;
    for (int i = 20; i >= 0; --i)
    {
        int now = ((b[num] >> i) & 1);
        if (ch[u][now]) u = ch[u][now];
        else
        {
            ch[u][now] = ++node;
            u = node;
        }
    }
    ch[u][0] = num;
}

int findmx(int num)
{
    int u = 0;
    for (int i = 20; i >= 0; --i)
    {
        int now = ((b[num] >> i) & 1);
        if (ch[u][now ^ 1]) u = ch[u][now ^ 1];
        else u = ch[u][now];
    }
    return ch[u][0];
}

int main()
{
    scanf("%d", &n);
    scanf("%d", &a[0]);
    b[0] = a[0];
    ans = b[0];
    st = ed = 0;
    for (int i = 1; i < n; ++i) scanf("%d", &a[i]), b[i] = a[i] ^ b[i - 1];
    memset(ch, 0, sizeof(ch));
    node = 0;
    insert(0);
    for (int i = 1; i < n; ++i)
    {
        int j = findmx(i);
        if (ans < (b[i] ^ b[j]))
        {
            ans = b[i] ^ b[j];
            st = j + 1;
            ed = i;
        }
        insert(i);
    }
    printf("%d %d %d\n", ans, st+1, ed+1);
    return 0;
}
