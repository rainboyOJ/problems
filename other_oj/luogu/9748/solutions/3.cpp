// 变成了一个递归 算法,
#include <iostream>
using namespace std;
int n;
int a1,a2=-1;

void dfs(int dep,int x) {
    // cout << dep << " " << x << endl;
    if( x <= 0) {
        a1 = dep-1;
        return;
    }
    if( a2 == -1 && (x+2) % 3 == 0) {
        a2 = dep;
    }

    dfs(dep+1,x - (x+2)/3);
}
int main() {
    std::cin >> n;
    dfs(1,n);
    cout << a1 << " " << a2 << endl;

    return 0;
}
