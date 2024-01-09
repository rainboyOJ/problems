/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 02月 19日 星期六 15:55:07 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

int mg[100][100];
bool vis[100][100];
/* 顺时针-4个方向 */
int fx[][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

bool in_mg(int x,int y){
    return x>=1 && x <=5 && y >=1 && y <=5;
}

struct node {int x,y;};

int ans_len = 9999999;
node ans[100];

node t[100]; // tmp

void dfs(int x,int y,int dep){
    // 进入一个点
    t[dep].x = x;
    t[dep].y = y;
    vis[x][y] = 1;
    
    if( x == 5 && y == 5 ){
        if( dep < ans_len){
            ans_len = dep;
            for(int i=1;i<=dep;i++){
                ans[i].x = t[i].x;
                ans[i].y = t[i].y;
            }
        }
        return;
    }

    for(int i=0;i<=3;++i){
        int nx = x+fx[i][0];
        int ny = y+fx[i][1];
        if( in_mg(nx, ny) && vis[nx][ny] == 0 && mg[nx][ny] == 0){
            dfs(nx,ny,dep+1);
            vis[nx][ny] =0;
        }
    }

}


int main(int argc,char * argv[]){
    for(int i=1;i<=5;++i){
        for(int j=1;j<=5;++j){
            scanf("%d",&mg[i][j]);
        }
    }
    dfs(1,1,1);
    for(int i=1;i<=ans_len;++i){
        printf("(%d, %d)\n",ans[i].x-1,ans[i].y-1);
    }
    return 0;
}
