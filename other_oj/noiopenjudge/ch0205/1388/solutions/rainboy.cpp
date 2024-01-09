#include <bits/stdc++.h>
using namespace std;

char _map[105][105];
bool vis[105][105];
int n,m;

int fx[][2] = { 0,1, 0,-1, 1,0, -1,0, 1,1, -1,1, 1,-1, -1,-1 };


void init(){
    memset(vis,0,sizeof(vis));
    scanf("%d%d",&n,&m);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%s",_map[i]+1);
    }
}



int cnt=0;

bool in_map(int x,int y){
    if( x >=1 &&  y >=1 &&  x <= n && y <=m )
        return 1;
    return 0;
}

void dfs(int x,int y){
    vis[x][y] = 1;

    int i;
    for (i=0;i<8;i++){
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        if( in_map(nx, ny) && !vis[nx][ny] && _map[nx][ny] == 'W'){
            dfs(nx,ny);
        }
    }
}
int main(){
    init();
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            if( !vis[i][j] && _map[i][j] == 'W'){
                cnt++;
                dfs(i,j);
            }
        }
    }
    printf("%d\n",cnt);
    return 0;
}
