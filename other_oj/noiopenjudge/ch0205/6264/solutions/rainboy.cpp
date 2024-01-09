#include <bits/stdc++.h>
using namespace std;

int n,m;
char maze[200][200];
bool vis[200][200];
int fx[][2] = { 1,0, -1,0, 0,1, 0,-1 };

int sx,sy,tx,ty;
struct pos {
    int x,y,step;
};


void init(){
    memset(vis,0,sizeof(vis));
    int i,j;
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++){
        scanf("%s",maze[i]+1);
        for (j=1;j<=m;j++){
            if( maze[i][j] == 'S')
                sx = i, sy = j;
            else if( maze[i][j] == 'T')
                tx = i, ty = j;
        }
    }
}
bool inmap(int x,int y){
    if( x >=1 && y>=1 && x <=n & y<=m)
        return 1;
    return 0;
}


int bfs(){
    queue<pos> q;
    q.push({sx,sy,0});
    vis[sx][sy] = 1;

    while( !q.empty()){
        pos h = q.front();q.pop();

        int i;
        for (i=0;i<4;i++){
            int nx = h.x+fx[i][0];
            int ny = h.y+fx[i][1];
            if( maze[nx][ny] == 'T'){
                return h.step+1;
            }

            if( inmap(nx, ny) && !vis[nx][ny] && maze[nx][ny] == '.'){
                vis[nx][ny] = 1;
                q.push({nx,ny,h.step+1});
            }
        }
    }

    return -1;
}
int main(){
    init();
    int ans = bfs();
    printf("%d\n",ans);
    return 0;
}
