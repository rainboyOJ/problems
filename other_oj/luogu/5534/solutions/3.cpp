#include <iostream>
using namespace std;

typedef long long ll;
ll a,b,n;
ll d; //差值

ll dfs(int dep) {
    //边界
    if( dep == 1) return a;
    return a + (dep-1) *d + dfs(dep-1);
}

int main() {
    std::cin >> a >> b >> n;
    d = b - a;
    cout << dfs(n) << endl;

    return 0;
}
