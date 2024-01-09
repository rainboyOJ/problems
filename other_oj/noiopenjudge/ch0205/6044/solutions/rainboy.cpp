/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 01月 24日 星期一 19:41:36 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m,T;
/* 定义全局变量 */

int sx,sy,tx,ty;
char _map[300][300];
bool vis[300][300][100];
struct node {
    int x,y,s,t;
};

/* 顺时针-4个方向 */
int fx[][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

bool in_mg(int x,int y){
    return x>=0 && x< n && y >=0 && y <m;
}

int bfs(int x,int y){
    queue<node> q;
    q.push({x,y,0,T});
    vis[x][y][T] = 1;
    //std::cout << x <<" "<< y <<" "<< 0 <<" "<< T << std::endl;
    while ( q.empty() ==false) {
        node h = q.front();
        q.pop();
        if( h.x == tx && h.y == ty) return h.s;
        for(int i=0;i<=3;++i){
            int nx = h.x + fx[i][0];
            int ny = h.y + fx[i][1];
            if( in_mg(nx, ny) ){
                if( _map[nx][ny] == '#' && h.t >=1  && vis[nx][ny][h.t-1] == 0){
                    vis[nx][ny][h.t-1] = 1;
                    q.push({nx,ny,h.s+1,h.t-1});
                    //std::cout << nx <<" "<< ny <<" "<< h.s+1 <<" "<< h.t-1 << std::endl;
                }
                else if( _map[nx][ny] != '#' && vis[nx][ny][h.t] == 0){
                    vis[nx][ny][h.t] = 1;
                    q.push({nx,ny,h.s+1,h.t});
                    //std::cout << nx <<" "<< ny <<" "<< h.s+1 <<" "<< h.t << std::endl;
                }
            }
        }
    }
    return -1;
}

int main(int argc,char * argv[]){
    std::cin >> n >> m >> T;
    for(int i=0;i<=n-1;++i){
        cin >> _map[i];
        //std::cout << _map[i] << endl;
        for(int j=0;j<=m-1;++j){
            if( _map[i][j] == '@'){
                sx = i;
                sy = j;
            }
            else if( _map[i][j] == '+'){
                tx = i;
                ty = j;
            }
        }
    }
    //std::cout << sx <<" "<< sy <<" "<< tx <<" "<< ty << std::endl;
    int ans = bfs(sx,sy);
    std::cout << ans << std::endl;
    return 0;
}
