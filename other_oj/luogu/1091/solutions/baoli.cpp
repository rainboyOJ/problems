#include <iostream>
using namespace std;

int n;
int a[10005];
int rcd[10005];

int ans;
//检查是否中间高 两边低
bool check() {

    int pre = -1;
    int last = 0;
    a[0] = -1;
    // 找到前面的上升的顶点,last
    for(int i =1;i<=n;i++) {
        if( rcd[i] == 1) {
            if( a[i] > pre) {
                last = i;
                pre = a[i];
            }
            else break;
        }
    }
    pre = a[last];
    // 从last开始后面应该都是下降的
    for(int i = last+1 ;i<=n;i++) {
        if( rcd[i] == 1) {
            if( a[i] < pre) {
                pre = a[i];
            }
            else return false;
        }
    }
    return true;
}

void dfs(int dep ) {
    if( dep > n) {
        if( check()) { //如果是中间高,两边低
            int cnt = 0;
            for(int i =1;i<=n;i++)
                cnt += rcd[i];// 记录有多少个元素
            if( cnt > ans) ans = cnt;
        }
        return;
    }
    rcd[dep] = 0;
    dfs(dep+1);
    rcd[dep] = 1;
    dfs(dep+1);
}

int main () {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
    dfs(1);
    cout << n - ans << endl;
    return 0;
}
