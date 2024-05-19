//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-01 14:38:21
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
long long a[maxn];

//求[l,r]的区间和 
long long range_sum(int l,int r)
{
    return a[r] - a[l-1];
}

int main (int argc, char *argv[]) {
    std::cin >> m;
    n = (m+1) / 2 +1;
    for(int i = 1;i <= n ;++i ) // i: 1->m
    {
        a[i] = a[i-1] + i; // 求前缀和
    }
    for(int i=1;i<=n;i++) {
        for(int j=n;j>=i;j--) {
            if( range_sum(i,j) == m)
            {
                cout << i << " " << j << endl;
                break;
            }
        }
    }

    return 0;
}
