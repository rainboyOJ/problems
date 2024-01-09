#include <bits/stdc++.h>
using namespace std;

int n;
int size;
int sx,sy,tx,ty;
bool vis[305][305];

int fx[][2] = { {2,-1}, {2,1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };
struct pos {
    int x,y,step;
};

void init(){
    scanf("%d",&size);
    scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
    memset(vis,0,sizeof(vis));
}

bool in_map(int x,int y){
    if(x >=0 && x < size && y >=0 && y < size)
        return 1;
    return 0;
 }

int bfs(){
    if( sx == tx && tx == ty){
        return 0;
    }
    queue<pos> q;
    q.push({sx,sy,0});
    vis[sx][sy] =1;

    while( !q.empty()){
        pos h  =q.front();q.pop();

        int i;
        for (i=0;i<8;i++){
            int nx = h.x +fx[i][0];
            int ny = h.y +fx[i][1];
            if( nx == tx && ny == ty){
                return h.step+1;
            }

            if( in_map(nx, ny) && vis[nx][ny] == 0 ){
                vis[nx][ny] = 1;
                q.push({nx,ny,h.step+1});
            }

        }

    }

    return -1;
}

int main(){
    scanf("%d",&n);
    while (n--) {
        init();
        int ans = bfs();
        printf("%d\n",ans);
    }
    return 0;
}
