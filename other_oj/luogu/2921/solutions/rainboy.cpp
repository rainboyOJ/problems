#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
const int maxe = 1e6 + 5;
int n;
int ans[maxn];
int deg[maxn]; //点的入度　
int deg2[maxn]; //点的入度　
int cnt_loop[maxn];
int vis[maxn];

std::queue<int> q;

struct linklist
{
    struct {int v,w,next;} e[2*maxe];
    int head[maxn],cnt;

    void init() {
        cnt = 0;
        memset(head,-1,sizeof(head ));
    }

    void add(int u,int v,int w)
    {
        e[cnt] = {v,w,head[u]};
        head[u] = cnt++;
    }
    void add2(int u,int v,int w){
        add(u,v,w); add(v,u,w);
    }
};

linklist g;
linklist g2; // 反向的

void init(){
    g.init();
    g2.init();
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        g.add(i,v,0);
        g2.add(v,i,0);
        deg[v]++;
        deg2[v]++;
    }
}

void topsort() {
    for(int i = 1; i <= n; i++)
        if( deg[i]== 0) q.push(i);
    while(!q.empty()) {
        int u = q.front();
        // cout << "out dequeue " << u << endl;  
        q.pop();
        for(int i = g.head[u]; i!= -1; i = g.e[i].next)
        {
            int v = g.e[i].v;
            if( --deg[v] == 0) q.push(v);
        }
    }
}

int loop_node = 0;
//求环上的点的数量
void dfs_loop(int u,int idx) {
    loop_node++;
    vis[u] = idx;
    for(int i = g.head[u]; i!= -1; i = g.e[i].next)
    {
        int v = g.e[i].v;
        if( vis[v] == 0)
            dfs_loop(v, idx);
    }
}

void dfs2(int u,int cnt) {
    ans[u] = cnt;
    for(int i = g2.head[u]; i!= -1; i = g2.e[i].next)
    {
        int v = g2.e[i].v;
        if(deg[v] == 0 ) {
            dfs2(v, cnt+1);
        }
    }
}


void work() {
    // 1. 找到哪个点在环上, deg[u] == 1
    topsort();
    // 2. 计算环上的点的数量　dfs
    int idx = 1;
    for(int i =1;i<=n;i++)
    {
        if(deg[i] == 1 && vis[i] == 0)
        {
            loop_node = 0;
            dfs_loop(i,idx);
            cnt_loop[idx] = loop_node;
            idx++;
        }
    }
    // for(int i = 1; i <= n; i++)
    // {
    //     cout << i << " " << cnt_loop[ vis[i] ] << endl;
    // }
    // 3. 求答案
    for(int i =1;i<=n;i++)
    {
        if( deg[i] == 1) ans[i] = cnt_loop[ vis[i] ];
        if( deg2[i] > 1 )
        {
            if( deg[i] == 1)
            {
                // cout << "error" << i << endl;
                dfs2(i,cnt_loop[vis[i]]);
            }
        }
    }
}

int main() {
    init();
    // cout << g.cnt << endl;
    work();
    for(int i = 1; i <= n; i++)
    {
        cout << ans[i] << "\n";
    }
    return 0;
}
