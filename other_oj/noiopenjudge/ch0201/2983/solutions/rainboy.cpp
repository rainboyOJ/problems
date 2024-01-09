#include <bits/stdc++.h>
using namespace std;

int a[205];
int cnt[205]  ={0} ;
int n,m;

int main(){
    scanf("%d%d",&n,&m);
    int i,t;
    for(i=1;i<=n;i++){
        scanf("%d",&t);
        a[i] = t;
        cnt[t]++;
    }
    for(i=1;i<=n;i++){
        if(cnt[ a[i] ] < 2)
            printf("BeiJu\n");
        else
            printf("%d\n",cnt[a[i]]-1);
    }
    return 0;
}
