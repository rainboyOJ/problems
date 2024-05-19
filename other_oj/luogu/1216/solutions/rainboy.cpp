#include <iostream>
using namespace std;
const int maxn = 1000 +5;

int n;
int a[maxn][maxn];
int f[maxn][maxn];
int ans;

void init() {
    cin >> n;
    for(int i =1;i<=n ;i++){
        for(int j =1;j<=i;j++)
            cin >> a[i][j];
    }
    for(int i =0;i<=1000;i++)
        for (int j = 0; j <= 1000; j++)
            f[i][j] = -1;
}

// dfs(i,j) 表示从i,j这个点开始向下走,到
// 最后一层的最值
int dfs(int i,int j)
{
    if( i == n+1) {
        return 0;
    }
    if( f[i][j] != -1)
        return f[i][j];
    
    int x = dfs(i+1,j);
    int y = dfs(i+1,j+1);

    if( x > y)
        f[i][j] = x;
    else
        f[i][j] = y;
    f[i][j] += a[i][j];
    return f[i][j];

}

int main(int argc, char const *argv[])
{
    init();
    dfs(1,1);
    cout << f[1][1] << endl;
    return 0;
}

