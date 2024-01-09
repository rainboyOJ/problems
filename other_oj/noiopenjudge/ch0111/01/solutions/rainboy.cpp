#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int a[maxn];
int n;
int m;
bool check(int m,int val){
    return a[m] >= val;
}
int bs_find(int l,int r,int val)
{
    while(l < r) {
        int mid = (l+r) >> 1;
        if( check(mid,val) == true) 
            r = mid;
        else 
            l = mid+1;
    }
    return l;
}

int main(){
    cin >> n;

    for(int i =1;i<=n;i++)
        cin >> a[i];
    // sort(a+1,a+1+n);
    cin >> m;
    for(int i =1;i<=m;i++){

        int t;
        cin >> t;
        int pos = bs_find(1,n+1,t);
        if( pos == n+1)
            cout << a[n] << endl;
        else if( pos == 1){
            cout << a[1] << endl;;
        }
        else if(a[pos] - t >= t-a[pos-1]){
            cout << a[pos-1] << endl;
        }
        else 
            cout << a[pos] << endl;
    }
    
    return 0;
}