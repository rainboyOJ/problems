#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;

int n,k;
int a[maxn];


// len = length
int num(int len){
    int cnt = 0;
    for(int i =1;i<=n;i++){
        cnt += a[i] / len;
    }
    return cnt;
}

int mid(int l,int r) {
    return (l+r) >> 1; //这是最快的写法
}

//检查pos位置的值是否符合要求
bool check(int len){
    int cnt = num(len);
    return cnt >= k;
}

//bs_find = binary search find
int bs_find(int l,int r) {
    while( l < r) {
        int m = mid(l,r);
        if( !check(m))//不成立
            r = m;
        else //成立,抛弃左半边
            l = m+1;
    }
    return l ;
}

int main(){
    cin >> n >> k;
    for(int i =1;i<=n;i++){
        double t;
        cin >> t;
        a[i] = t *100;
    }
    // 1km = 1000m
    // 1m = 100 cm
    // 1km = 1000 * 100 cm
    int ans = bs_find(1,100*1000*100+1);
    ans--;
    cout << fixed << setprecision(2) << ans *1.0 / 100 << endl;
    return 0;
}