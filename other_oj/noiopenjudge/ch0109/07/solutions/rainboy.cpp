#include <cstdio>
#include <cstring>

#define inf 0x7f7f7f7f

int n;
int a[200];
int max = -inf;
int main(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if( max  < a[i])
            max = a[i];
    }
    int sum = 0;
    for (i=1;i<=n;i++){
        if( max != a[i])
            sum += a[i];
    }
    printf("%d\n",sum);
    return 0;
}
