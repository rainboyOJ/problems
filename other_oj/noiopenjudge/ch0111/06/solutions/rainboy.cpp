#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;

int n,m;
int a[maxn];

bool check(int val) {
    int cnt = 0;
    int sum =0;
    for(int i =1;i<=n;i++){
        if( sum + a[i] > val) {
            cnt++;
            sum = a[i];
            if( sum > val) return false; // 一件物品都装不下
        } else {
            sum += a[i];
        }
    }
    cnt++;
    return cnt <=m;
}

// bs = binary search
int bs_find(int l,int r) {
    while(l < r) {
        int mid = (l+r) >> 1;
        if( check(mid) ) { // 红色
            r = mid;
        } else { // 蓝色
            l = mid+1;
        }
    }
    return l;

}


int main(){
    cin >> n >> m;
    for(int i =1;i<=n;i++){
        cin >> a[i];
    }
    
    int pos = bs_find(1,10000 * 100000+1);
    cout << pos << endl;
    return 0;
}