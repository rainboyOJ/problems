//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-30 19:55:41
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
char a[105][305];
bool vis[105][305]; //某个点是否访问过
int cnt;

int fx[4][2] = {
    1,0,
    0,1,
    0,-1,
    -1,0
};

//在地图内
bool in_map(int x,int y) {
    return x>=1 && x <=n && y >=1 && y <=200;
}

void dfs(int x,int y) {
    vis[x][y] = cnt;

    for(int i = 0;i <= 3 ;++i ) // i: 0->3
    {
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        if( !in_map(nx,ny)) continue;
        if( vis[nx][ny] != 0) continue;
        char c = a[nx][ny];
        if( c >='a' && c <='z')
            dfs(nx,ny);
    }
}

int main (int argc, char *argv[]) {
    std::cin >> n;
    cin.getline(a[0]+1,205); //注意第一行后面还有换行符号

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin.getline(a[i]+1,205);
        // cout << a[i]+1 << endl;
    }
    
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1 ;j<=200;j++) {
            if( a[i][j] >='a' && a[i][j] <='z') //是人
            {
                if(vis[i][j]) continue; //访问过
                cnt++;
                dfs(i,j); //从这个位置开始染色
            }
        }
    }
    //输出最后有多少的颜色
    cout << cnt << endl;
    return 0;
}
