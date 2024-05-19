#include <iostream>
#include <cstring>
using namespace std;
// f(i,j) = min( 
// f(i-1,j-1), f(i-1,j) + 1 ,f(i,j-1) +1,f(i-1,j-1) +1

char a[10000];
char b[10000];

int f[2005][2005];


int dfs(int i,int j) {
    // 边界
    if( i == 0 || j == 0) {
        return i+j;
    }
    //记忆化
    if( f[i][j] !=0) return f[i][j];
    int cnt = 0x7f7f7f7f;
    // 32位 0b01111111111111 -> 0x7ffffffff
    if( a[i] == b[j]) {
        cnt = min(cnt,dfs(i-1,j-1));
    }
    cnt = min( cnt,dfs(i-1,j)+1);
    cnt = min( cnt,dfs(i,j-1)+1);
    cnt = min( cnt,dfs(i-1,j-1)+1);
    f[i][j] = cnt;
    return cnt;
}

int main() {
    cin >> a+1;
    cin >> b+1;
    int l1 = strlen(a+1);
    int l2 = strlen(b+1);

    int ans = dfs(l1,l2);
    cout << ans <<endl;



    return 0;
}
