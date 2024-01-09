#include <cstdio>
#include <cstring>

int n;

int fac(int n){
    if( n ==2 || n==1)
        return 1;

    return fac(n-1)+fac(n-2);
}

int main(){
    scanf("%d",&n);
    int i,t;
    for(i=1;i<=n;i++){
        scanf("%d",&t);
        int ans = fac(t);
        printf("%d\n",ans);
    }
    return 0;
}
