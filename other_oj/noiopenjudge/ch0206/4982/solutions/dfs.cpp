#include <iostream>
using namespace std;

int n;

long long f[100][100];
bool vis[100][100];
int ans;
int sx = 1;
int sy = 40;

struct node {
    int x,y;
};

node p[1000];
int cnt;

void push(int x,int y) {
    ++cnt;
    p[cnt].x = x;
    p[cnt].y = y;
}

int abs(int a) {
    if( a < 0) return -a;
    return a;
}

//ｘ，ｙ到起点ｓｘ，ｓｙ的距离
int mhd_dis(int x,int y){
    return abs(x-sx) + abs(y-sy);
}

void dfs(int dep,int x,int y) {
    if( dep == n) {
        // cout << x << " " << y<<endl;
        ans++;
        return ;
    }
    
    vis[x][y] = 1;


    if( vis[x+1][y] == 0)
        dfs(dep+1,x+1,y);
    if( vis[x][y-1] == 0)
        dfs(dep+1,x,y-1);
    if( vis[x][y+1] == 0)
        dfs(dep+1,x,y+1);

    vis[x][y] = 0;
}





int main() {
    cin >> n;
    dfs(0,sx,sy);
    cout << ans << endl;

    return 0;
}
