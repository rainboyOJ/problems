#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e4+10;
const int base = 1e5+1;
const int m = base*2;
int n, s;
int l[maxn], r[maxn];
ll f[maxn][2];

struct SegmentTree
{
    int l, r;
    int id;
    int laz;
    #define lson (p<<1)
    #define rson (p<<1|1)
    #define l(x) tree[x].l
    #define r(x) tree[x].r
    #define id(x) tree[x].id
    #define laz(x) tree[x].laz
}tree[m<<2];

void spread(int p)
{
    if(laz(p))
    {
        laz(lson) = laz(rson) = 1;
        id(lson) = id(rson) = id(p);
        laz(p) = 0;
    }
}

void build(int p, int l, int r)
{
    l(p) = l, r(p) = r;
    if(l == r) return;
    int mid = (l+r)>>1;
    build(lson, l, mid); build(rson, mid+1, r);
}

int ask(int p, int x)
{
    if(l(p) == r(p)) return id(p);
    int mid = (l(p)+r(p))>>1;
    spread(p);
    if(x <= mid) return ask(lson, x);
    else return ask(rson, x);
}

void change(int p, int L, int R, int v)
{
    if(L <= l(p) && r(p) <= R) {
        id(p) = v;
        laz(p) = 1;
        return;
    }
    spread(p);
    int mid = (l(p)+r(p))>>1;
    if(L <= mid) change(lson, L, R, v);
    if(mid < R) change(rson, L, R, v);
}

int main()
{
    scanf("%d%d", &n, &s);
    s += base;
    build(1, 1, m);
    //直接走回原点
    l[0] = r[0] = base;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &l[i], &r[i]);
        l[i] += base; r[i] += base;
        int lv = ask(1, l[i]);
        int rv = ask(1, r[i]);
        f[i][0] = min(f[lv][0]+abs(l[lv]-l[i]), f[lv][1]+abs(r[lv]-l[i]));
        f[i][1] = min(f[rv][0]+abs(l[rv]-r[i]), f[rv][1]+abs(r[rv]-r[i]));
        change(1, l[i], r[i], i);
    }

    int ans = min(f[n][0]+abs(l[n]-s), f[n][1]+abs(r[n]-s));
    cout << ans << endl;
    return 0;
}
