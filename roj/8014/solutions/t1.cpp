//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-01 15:31:39
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int t1,t2;
int a[maxn];

long long ans = 0;

//求数字a的约数个数
//数字原理
long long cnt_of_ys(int a) {
    int n = a;
    int s = 1;
    for (int i = 2; i * i <= n; i++)
    {
        int r = 0;
        while (n % i == 0)
        {
            r++;
            n /= i;
        }
        if (r > 0)
        {
            r++;
            s *= r;
        }
    }
    if (n > 1) s *= 2;
    return s;
}

int main (int argc, char *argv[]) {
    std::cin >> t1 >> t2;
    if( t1 > t2) swap(t1,t2);
    for(int i = t1;i <= t2 ;++i ) // i: t1->t2
    {
        long long t = cnt_of_ys(i);
        // cout << i << " " << t << endl;
        ans += t;
    }
    std::cout << ans << "\n";
    return 0;
}
