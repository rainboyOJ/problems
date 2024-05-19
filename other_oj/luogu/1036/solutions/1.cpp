//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-19 17:09:57
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,k;
int a[maxn];
int b[maxn]; //桶
int ans;

bool is_prime(int n) {
    if( n < 2) return 0;
    for(int i = 2;i*i <= n;i++) {
        if( n % i == 0) return 0;
    }
    return 1;
}

void dfs(int dep) {
    if( dep > n) {
        //判断是否有k个选取了
        int cnt  = 0;
        int sum = 0;
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            // cout << b[i] << " ";
            cnt += b[i];
            if( b[i]) sum += a[i];
        }
        // std::cout  << "\n";
        if( cnt != k) return;
        // for(int i = 1;i <= n ;++i ) // i: 1->n
        // {
        //     if( b[i])  cout << a[i] << " + ";
        // }
        // cout << " = " << sum << endl;
        if( is_prime(sum)) ans++;
        return ;
    }
    for(int i = 0;i <= 1 ;++i ) // i: 0->1
    {
        b[dep] = i;
        dfs(dep+1);
    }

}

int main (int argc, char *argv[]) {
    std::cin >> n >> k;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
    dfs(1);
    std::cout << ans << "\n";
    return 0;
}
