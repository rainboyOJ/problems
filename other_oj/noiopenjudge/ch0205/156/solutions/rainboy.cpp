#include <bits/stdc++.h>
using namespace std;


int r,c;
int fx[][2] = { 1,0, -1,0, 0,1, 0,-1, };
bool vis[30][30];
bool mark[400];
char _map[30][30];
int ans = 0;
void init(){
    scanf("%d%d",&r,&c);
    int i,j;
    for (i=1;i<=r;i++){
        scanf("%s",_map[i]+1);
    }
}

bool in_map(int x,int y){
    if( x >=1 && x <=r  && y >= 1 && y <=c )
        return 1;
    return 0;
}


void dfs(int x,int y,int dep){
    ans = max(ans,dep+1);
    vis[x][y] = 1;
    mark[ _map[x][y] ] = 1;

    int i;
    for (i=0;i<4;i++){
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        if(in_map(nx, ny) && !vis[nx][ny] && !mark[_map[nx][ny]]){
            dfs(nx,ny,dep+1);
            vis[nx][ny]  = 0;
            mark[ _map[nx][ny] ] = 0;
        }
    }
}


int main(){
    init();
    dfs(1,1,1);
    printf("%d\n",ans-1);
    return 0;
}
