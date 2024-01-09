/* 高精乘单精 */
#include <cstdio>

int a[10000000] = {1};
int cnt = 1;
int n;
int main(){
    scanf("%d",&n);
    int i,j,k;
    for(i=1;i<=n;i++){
        for(j=0;j<cnt;j++){
            a[j] *= i;
        }
        int pre =0;
        for(j=0;j<cnt;j++){
            int t = (a[j] + pre) % 10;
            pre = (a[j] + pre) / 10;
            a[j] = t;
        }
        while( pre != 0){
            a[cnt++] = pre %10;
            pre /=10;
        }
    }
    for(i=cnt-1;i>=0;i--)
        printf("%d",a[i]);
    return 0;
}
