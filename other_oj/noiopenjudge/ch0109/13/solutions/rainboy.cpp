#include <cstdio>
#include <cstring>
int n;
int cnt[200] = {0};
int a[20009];
int main(){
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        a[i] = t;
        cnt[t] = 1;
    }
    for (i=1;i<=n;i++){
        if( cnt[a[i]]){
            printf("%d ",a[i]);
            cnt[a[i]]--;
        }
    }
    return 0;
}
