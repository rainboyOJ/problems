#include <bits/stdc++.h>
using namespace std;

int n,m;
int _map[100][100];
bool vis[100][100];
int cnt_room=0,area=0,area_tmp;

int fx[][2] = {
    /* west */  0,-1,
    /* north */ -1,0,
    /* east */  0,1,
    /* south */ 1,0
};

bool in_map(int x,int y){
    if( x >=1 && x <= n && y >=1 && y <=m)
        return 1;
    return 0;
}

//dir 0 1 2 3 => west,north,east,south
bool is_dir_ok(int x,int y,int dir){
    int nx,ny;
    int to_dir;
    if( dir == 0 || dir == 2){
        to_dir = 2 - dir;
    }
    else { // dir == 1 or 3
        to_dir = 4-dir;
    }

    nx = x + fx[dir][0];
    ny = y + fx[dir][1];

    if( (_map[x][y] & (1<<dir) ) == 0 
            && in_map(nx, ny)
            && (_map[nx][ny] & (1<<to_dir)) == 0
        ){

        return 1;
    }
    return 0;
}

void init(){
    scanf("%d%d",&n,&m);
    memset(vis,0,sizeof(vis));
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            scanf("%d",&_map[i][j]);
        }
    }
}


void dfs(int x,int y){
    vis[x][y] = 1;
    area_tmp++;

    int i;
    for(i=0;i<4;i++){
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        if( is_dir_ok(x, y, i) && !vis[nx][ny])
            dfs(nx,ny);
    }
}

int main(){
    init();
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            if(!vis[i][j]){
                cnt_room++;
                area_tmp = 0;
                dfs(i,j);
                area= max(area,area_tmp);
            }
        }
    }
    printf("%d\n",cnt_room);
    printf("%d\n",area);
    return 0;
}
