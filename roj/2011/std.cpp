/*
TASK:calfflac
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 20005;

char text[MAXN + 1000], mc[MAXN * 2];
int f[MAXN * 2], key[MAXN * 2], totlen, n, maxr, ans;

bool check(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char upcase(char c)
{
    if (c >= 'A' && c <= 'Z') return c;
    else return c - 'a' + 'A';
}

int main()
{
    totlen = 0;
    while (fgets(mc, 100, stdin))
    {
        n = strlen(mc);
        for (int i = totlen; i < totlen + n; ++i)
            text[i] = mc[i - totlen];
        totlen += n;
    }
    n = 0;
    memset(mc, 0, sizeof(mc));
    for (int i = 0; i < totlen; ++i)
        if (check(text[i])) mc[n++] = upcase(text[i]), key[n-1] = i, mc[n++] = '#';
    memset(f, 0, sizeof(f));
    maxr = 0;
    ans = 0;
    for (int i = 1; i < n; ++i)
    {
        if (maxr + f[maxr] >= i)
        {
            int j = 2 * maxr - i;
            if (j - f[j] >= maxr - f[maxr]) f[i] = f[j];
            else
            {
                int l = 0;
                f[i] = j - maxr + f[maxr];
                while (mc[i - f[i] - l - 1] == mc[i + f[i] + l + 1]) l++;
                f[i] += l;
                if (mc[i + f[i]] == '#' && f[i] > 0) f[i]--;
                if (maxr + f[maxr] < i + f[i]) maxr = i;
                if (f[ans] < f[i]) ans = i;
            }
        }
        else
        {
            int l = 0;
            while (mc[i - l - 1] == mc[i + l + 1]) l++;
            f[i] = l;
            if (mc[i + f[i]] == '#' && f[i] > 0) f[i]--;
            if (maxr + f[maxr] < i + f[i]) maxr = i;
            if (f[ans] < f[i]) ans = i;
        }
    }
    printf("%d\n", f[ans] + 1);
    for (int i = key[ans - f[ans]]; i <= key[ans + f[ans]]; ++i) printf("%c", text[i]);
    printf("\n");
    return 0;
}
