/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 09月 27日 星期日 14:46:29 CST */
#include <bits/stdc++.h>
using namespace std;

#ifndef DEBUG
#define debug(...)
#endif

const int maxn = 1e5+5;
int n,m;
int a[maxn];
int b[maxn];

int bs(int l,int r,int key){
    while ( l < r){
        int m = (l+r) >>1;
        if( a[m] < key) l = m+1;
        else r = m;
    }
    return l;
}


int main(){
    scanf("%d",&n);
    int i,j;
    for(i=1;i<=n;++i) {
        scanf("%d",&a[i]);
        b[i] = a[i];
    }
    sort(a+1,a+1+n);
    //去重
    int idx=1;
    for(i=2;i<=n;++i){
        if( a[i] != a[i-1]) a[++idx] = a[i];
    }
    for(i=1;i<=n;++i){
        int pos = bs(1,n+1,b[i]);
        printf("%d ",pos);
    }

    return 0;
}
