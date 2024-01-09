#include <cstdio>
int n;
int a[1005];
int b[1005];

int main(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for (i=1;i<=n;i++){
        scanf("%d",&b[i]);
    }
    int sum = 0;
    for (i=1;i<=n;i++){
        sum += a[i]*b[i];
    }
    printf("%d\n",sum);
    return 0;
}
