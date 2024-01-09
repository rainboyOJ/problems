#include <bits/stdc++.h>
using namespace std;

bool vis[105][105];

struct pos {
    int x,y;
};
int p,q;
pos sta[10005];

int dx[8]= {-1,1,-2,2,-2,2,-1,1};
int dy[8]= {-2,-2,-1,-1,1,1,2,2};
int fx[8][2];

void init(){
    memset(vis,0,sizeof(vis));
    scanf("%d%d",&p,&q);
}

bool in_map(int x,int y){
    if( x >=1 && x <= p && y >=1 && y <=q)
        return 1;
    return 0;
}

bool dfs(int x,int y,int dep){
    vis[x][y] = 1;
    sta[dep] = {x,y};
    if( dep == p*q) {
        return 1;
    }
    
    int i;
    for (i=0;i<8;i++){
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        if(in_map(nx,ny) && !vis[nx][ny]){
            if( dfs(nx,ny,dep+1))
                return 1;
            vis[nx][ny] = 0;
        }
    }
    return 0;
}

int main(){
    int T;
    int cnt = 0;
    scanf("%d",&T);
    int i,j,k;
    for( i = 0;i< 8;i++){
        fx[i][0] = dx[i];
        fx[i][1] = dy[i];
    }
    while (T--) {
        printf("Scenario #%d:\n",++cnt);
        init();
        bool flag = false;
        for (i=1;i<=p;i++){
            for (j=1;j<=q;j++){
                memset(vis,0,sizeof(vis));
                if( dfs(i,j,1)){
                    for(k = 1;k<=p*q;k++){
                        printf("%c%d",sta[k].y+'A'-1,sta[k].x);
                    }
                    printf("\n");
                    flag = true;
                    break;
                }
            }
            if( flag) break;
        }
        if( !flag)
            printf("impossible\n");
        if( T != 0)
            printf("\n");
    }
    return 0;
}
