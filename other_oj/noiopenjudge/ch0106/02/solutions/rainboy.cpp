#include <cstdio>

int n=10,h;
int a[10+5];

int main(){
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&h);
    h += 30;
    int cnt = 0;
    for (i=1;i<=n;i++){
        if( h >= a[i]){
            cnt++;
        }
    }
    printf("%d",cnt);

    return 0;
}

