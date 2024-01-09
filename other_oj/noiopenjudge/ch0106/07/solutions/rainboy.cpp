#include <cstdio>

/* 对差值进行记数 ,a[1] = 1*/
int cnt[3005] = {0};

int main(){
    int n;
    scanf("%d",&n);
    int i;
    int a,b;
    scanf("%d",&a);
    for (i=2;i<=n;i++){
        scanf("%d",&b);
        int cha = b - a;
        if( cha < 0)
            cha = -cha;
        cnt[cha]++;
        a = b;
    }

    for(i=1;i<=n-1;i++){
        if( cnt[i] != 1){
            printf("Not jolly");
            return 0;
        }
    }
    printf("Jolly");
    return 0;
}
