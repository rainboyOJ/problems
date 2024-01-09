#include <bits/stdc++.h>
using namespace std;

int a[20];
int n;


void init(){
    int t;
    n = 0;
    while (scanf("%d",&t)) {
        if( t == 0) break;
        a[++n] = t;
    }
}
int main(){
    init();
    sort(a+1,a+1+n);
    int ans = 0;
    int i,j;
    for (i=1;i<n;i++){
        for(j=i+1;j<=n;j++){
            if( a[j] == a[i]*2){
                ans++;
                //printf("%d %d\n",i,j);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
