#include <bits/stdc++.h>
using namespace std;

int n,m,sx,sy;
int cnt ;
bool vis[305][305];

int fx[][2] = { {2,-1}, {2,1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };

void init(){
    cnt = 0;
    scanf("%d%d%d%d",&n,&m,&sx,&sy);
    sx++;
    sy++;
    memset(vis,0,sizeof(vis));
}

bool in_map(int x,int y){
    if(x >=1 && x <= n&& y >=1 && y <= m)
        return 1;
    return 0;
 }

void  dfs(int x,int y,int dep){
    if( dep == n*m){
        cnt++;
        return;
    }

    vis[x][y] = 1;

    int i;
    for (i=0;i<8;i++){
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        if( in_map(nx, ny) && !vis[nx][ny]){
            dfs(nx,ny,dep+1);
            vis[nx][ny] = 0;
        }
    }
}


int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
        init();
        dfs(sx,sy,1);
        printf("%d\n",cnt);
    }
    return 0;
}
