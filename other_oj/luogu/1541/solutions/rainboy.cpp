#include <iostream>
#include <cstring>
using namespace std;
int n;

int val[10005];
int f[50][50][50][50];

int dfs(int a,int b,int c,int d) {
    if( a + b +c +d == 0) {
        return val[1];
    }
    if( f[a][b][c][d] != -1 )
        return f[a][b][c][d];

    int tot = a+b*2+c*3+d*4;
    int ans =0;
    if( a > 0 && ans > dfs(a-1,b,c,d))  
        ans = dfs(a-1,b,c,d);

    if( b > 0 && ans > dfs(a,b-1,c,d))  
        ans = dfs(a,b-1,c,d);

    if( c > 0 && ans > dfs(a,b,c-1,d))  
        ans = dfs(a,b,c-1,d);

    if( d > 0 && ans > dfs(a,b,c,d-1))  
        ans = dfs(a,b,c,d-1);
    ans += val[tot+1];

    f[a][b][c][d] = ans;
    return ans;
}

int main () {
    memset(f,-1,sizeof(f));
    return 0;
}
