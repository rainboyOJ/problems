#include <cstdio>
#include <cmath>
int n;
int cnt[10005] = {0};
int main(){
    scanf("%d",&n);
    int max=-1;
    int i,t;
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        cnt[t]++;
        if( max < t)
            max =t;
    }
    for (i=0;i<=max;i++){
        printf("%d\n",cnt[i]);
    }
    return 0;
}
