#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int a[maxn];
int L;
int n;
int m;
bool check(long long min_jump){
    int pre = 0; //上一个没有删除的石头的下标
    int cnt = 0;
    for(int i =1;i<=n;i++) {
        if( a[i] - a[pre] < min_jump)
        {
            cnt++;
            if( cnt > m) return 0; //超过了删除的石头的个数
        }
        else {
            pre = i; //当前作为不删除的上一个石头的下标
        }
    }

    //特判，
    if( a[n+1] - a[pre] < min_jump) {
        cnt++;
    }
    if (cnt > m)
        return 0;
    return 1;
}

long long bs_find(long long l,long long r) {
    while( l < r) {
        long long mid = (l+r) >>1;
        
        if( !check(mid) ) 
            r = mid;
        else
            l = mid+1;
    }
    return l;
}

void init() {
    cin >> L >> n >> m;
    a[0] = 0;
    for(int i =1;i<=n;i++)
        cin >> a[i];    
    a[n+1] = L;
}

int main() {
    init();
    int ans = bs_find(1,1e9+5);
    cout << ans - 1;
    // for(int i=1;i<=11;i++) {
    //     cout << i << " " << check(i) << endl;
    // }
    return 0;
}