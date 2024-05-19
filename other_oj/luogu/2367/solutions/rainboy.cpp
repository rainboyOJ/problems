#include <iostream>
using namespace std;

const int maxn = 5e6+5;

int n,q;
int a[maxn]; //原数组
int b[maxn]; //差分数组

//区间修改
void add_range(int l,int r,int v)
{

    b[l] += v;
    b[r+1] -= v;
}

int main() {
    std::cin >> n >> q;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        b[i] = a[i] - a[i-1]; // 这里 b[1] 是多少呢?
    }
    for(int i = 1;i <= q ;++i ) // i: 1->q
    {
        int l,r,v;
        std::cin >> l >> r;
        std::cin >> v;
        add_range(l,r,v);
    }

    int sum = 0;
    int ans = 1e9;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        sum += b[i];
        // cout << b[i]<< endl;
        if( ans > sum)
            ans = sum;
    }
    cout << ans;



    return 0;
}

