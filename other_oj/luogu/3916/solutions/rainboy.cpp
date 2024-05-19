#include <cstdio>
#include <cstring>

const int maxn = 1e5+5;
int n,m;

int edge_cnt = 0;
int head[maxn];
struct {int u,v,next;} e[maxn];
bool vis[maxn];
int ans[maxn];

void addedge(int u,int v){
    edge_cnt++;
    e[edge_cnt] = {u,v,head[u]};
    head[u] = edge_cnt;
}

void dfs(int u,int pre){
    vis[u] = 1;
    ans[u] = pre;
    int i;
    for(i = head[u];i != -1 ;i = e[i].next){
        int v= e[i].v;
        if( vis[v] == 0)
            dfs(v,pre);
    }
}


int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    int i,j,u,v;
    for(i=1;i<=m;++i){
        scanf("%d%d",&u,&v);
        //addedge(u, v);
        addedge(v, u);
    }
    for(i =n;i>=1;i--){
        if( vis[i] == 0)
            dfs(i,i);
    }
    for(i=1;i<=n;++i){
        printf("%d ",ans[i]);
    }
    printf("\n");
    return 0;
}


