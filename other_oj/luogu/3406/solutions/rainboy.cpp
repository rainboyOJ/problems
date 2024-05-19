#include <iostream>
using namespace std;

const int maxn = 1e5+5;
int n,m;
int d[maxn];


int main() {
    cin >> n >> m;
    int pre;
    cin >> pre;
    for(int i = 2;i <= m ;++i ) // i: 1->m
    {
        int t;
        std::cin >> t;
        int l = pre;
        int r = t;

        if( l > r) swap(l,r);
        // cout << l<< " " << r << endl;
        //走了l,-> r-1,这段路
        d[l] +=1;
        d[r] -=1;

        pre = t;
    }
    long long ans = 0;


    //计算每一段路的次数
    for(int i = 1;i < n ;++i ) // i: 1->n
    {
        d[i] += d[i-1];
        // cout << d[i] << endl;
    }

    for(int i = 1;i < n ;++i ) // i: 1->n
    {
        long long a,b,c;
        std::cin >> a >> b >> c;
        long long t1 = a * d[i];
        long long t2 = b * d[i] + c;
        // cout << t1 << " " << t2 << endl;
        ans += min(t1,t2);
    }
    cout << ans <<endl;

    return 0;
}
