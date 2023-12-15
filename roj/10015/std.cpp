#include<bits/stdc++.h>
#define int long long
using namespace std;
int Read() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-')  f = -1; ch = getchar();}
    while(isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
    return x * f;
}
int first[1000005], nxt[1000005], to[1000005], tot = 0;
void Add(int x, int y) {
    nxt[++tot] = first[x];
    first[x] = tot;
    to[tot] = y;
}
int n, m, k, l, r, dis[500005], ts[500005], yts[500005], vis[500005];
void bfs() {
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(ts[i])  q.push(i), q.push(0), vis[i] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        int t = q.front(); q.pop();
        dis[u] = t;
        for(int e = first[u]; e; e = nxt[e]) {
            int v = to[e];
            if(!vis[v]) {
                q.push(v); vis[v] = 1;
                q.push(t + 1);
            }
        }
    }
    for(int i = 1; i <= n; i++)
        if(dis[i] >= l && dis[i] <= r)  yts[i] = 1;
    memset(dis, 0, sizeof(dis));
}
int cnt[500005], ycnt[500005], ydis[500005], dis2[500005], ans[500005];
void dfs1(int u, int fa) {
    cnt[u] = ts[u];  ycnt[u] = yts[u];
    for(int e = first[u]; e; e = nxt[e]) {
        int v = to[e];
        if(v == fa)  continue;
        dfs1(v, u);
        cnt[u] += cnt[v];
        ycnt[u] += ycnt[v];
        dis2[u] += dis2[v] + dis[v] * 2 + cnt[v];
        dis[u] += dis[v] + cnt[v];
        ydis[u] += ydis[v] + ycnt[v];
    }
}
void dfs2(int u, int fa) {
    for(int e = first[u]; e; e = nxt[e]) {
        int v = to[e];
        if(v == fa)  continue;
        if(cnt[u] > cnt[v])  dis2[v] += (dis2[u] - dis2[v] - dis[v] * 2 - cnt[v]) + (dis[u] - dis[v] - cnt[v]) * 2 + (cnt[u] - cnt[v]);
        dis[v] += cnt[u] - cnt[v] + (dis[u] - dis[v] - cnt[v]);
        ydis[v] += ycnt[u] - ycnt[v] + (ydis[u] - ydis[v] - ycnt[v]);
        cnt[v] = cnt[u], ycnt[v] = ycnt[u];
        dfs2(v, u);
    }
}
signed main() {
    n = Read(), m = Read(), k = Read(); l = Read(), r = Read();
    for(int i = 1; i < n; i++) {
        int x = Read(), y = Read();
        Add(x, y); Add(y, x);
    }
    for(int i = 1; i <= m; i++)
        ts[Read()] = 1;
    bfs(); dfs1(1, 0); dfs2(1, 0);
    for(int i = 1; i <= n; i++)  ans[i] = dis2[i] + ydis[i];
    for(int i = 1; i <= k; i++)  printf("%lld\n", ans[Read()]);
    return 0;
}