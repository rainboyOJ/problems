#include <cstdio>

int main(){
    int a[101];
    int n,m;
    int i;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    int cnt =0;
    for (i=1;i<=n;i++){
        if( a[i] == m)
            cnt++;
    }
    printf("%d",cnt);
    return 0;
}

