/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 05月 30日 星期日 19:08:10 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
int k;
/* 定义全局变量 */

bool vis[maxn];
struct node {
    int x,s;
};
queue<node> q;
int bfs(){
    q.push({n,0});
    vis[n] = 1;

    while ( !q.empty()) {
        node h = q.front();
        q.pop();
        if( h.x == k){
            return h.s;
        }

        int nex = h.x + 1;
        if( vis[nex] == 0){
            vis[nex] = 1;
            q.push({nex,h.s+1});
        }

        nex = h.x - 1;
        if( nex >=0 && vis[nex] == 0){
            vis[nex] = 1;
            q.push({nex,h.s+1});
        }

        nex = h.x * 2;
        if( nex <= 100000 && vis[nex] == 0){
            vis[nex] = 1;
            q.push({nex,h.s+1});
        }

    }
}

int main(){
    scanf("%d%d",&n,&k);
    if( n == k){
        printf("%d",0);
        return 0;
    }
    int ans = bfs();
    printf("%d",ans);

    return 0;
}
