/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 01月 02日 星期日 10:39:03 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
char mg[200][200]; // mg[0] --> &mg[0][0]
int sx,sy,zx,zy;

bool vis[200][200];
int fx[4][2] = {  {-1,0},{0,1},{1,0},{0,-1}};
//x,y是不是在迷宫内
bool in_mg(int x,int y){
    return x >=0 && x < n && y >=0 && y <n;
}
bool dfs(int x,int y){

    vis[x][y] = 1;
    if( x == zx && y == zy) 
        return true;
    for(int i=0;i<=3;++i){
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        if( in_mg(nx,ny) && vis[nx][ny] == 0 && mg[nx][ny] == '.'){
            if( dfs(nx,ny) )
                return true;
        }
    }
    return false;
}

int main(int argc,char * argv[]){
    int T;
    cin >> T; // 1
    while ( T-- ) {
        std::cin >> n;
        for(int i=1;i<=n;++i){
            cin >> mg[i-1];
        }
        std::cin >> sx >> sy >> zx >> zy;

        if( mg[sx][sy] == '#'){
            std::cout << "NO" << '\n' ;
            continue;
        }
        for(int i=0;i<=199;++i){
            for(int j=0;j<=199;++j){
                vis[i][j] = 0;
            }
        }
        bool ans = dfs(sx,sy);
        if( ans )
            std::cout << "YES" ;
        else
            std::cout << "NO" ;
        std::cout << '\n' ;
        //测试
        //for(int i=1;i<=n;++i){
            //cout << mg[i-1] << '\n';
        //}
        //std::cout << sx <<" "<< sy <<" "<< zx <<" "<< zy << std::endl;
    }

    return 0;
}
