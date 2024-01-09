#include <cstdio>
int a[105];
int n;
int main(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for (i=n;i>=1;i--){
        printf("%d ",a[i]);
    }
    return 0;
}
