#include <iostream>
using namespace std;

int s,n; // 起点,终点

int dfs(int n) {
    if( n <s) return 0 ;
    if( n == s) return 1;
    return dfs(n-1) + dfs(n-2);
}
int main () {
    std::cin >> s >> n;
    cout << dfs(n) << endl;
    return 0;
}
