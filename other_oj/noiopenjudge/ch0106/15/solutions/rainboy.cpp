/* 高精乘单精 */
/* 高精+高精 */
#include <cstdio>

int a[10000000] = {1};
int b[10000000] = {0};
int len_b = 1;
int cnt = 1;
int n;

void _add(){
    int i,j;
    int _max = len_b;
    if( len_b < cnt)
        _max = cnt;
    for (i=0;i<_max;i++){
        b[i+1] += (b[i]+a[i]) / 10;
        b[i] = (b[i]+a[i]) % 10;
    }
    if( b[_max] != 0)
        len_b = _max+1;
    else
        len_b = _max;

}
void p(){
    int i;
    for(i=cnt-1;i>=0;i--)
        printf("%d",a[i]);
    printf("\n");
    for(i=len_b-1;i>=0;i--)
        printf("%d",b[i]);
    printf("\n");
    printf("\n");
}
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

        _add();
        //p();
    }
    for(i=len_b-1;i>=0;i--)
        printf("%d",b[i]);
    return 0;
}
