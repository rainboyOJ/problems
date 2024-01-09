#include <cstdio> 
int main(){
    int n,x,y;
    scanf("%d%d%d",&n,&x,&y);
    int ans = y / x;
    if( y % x !=0)
        ans++;
    if( n - ans <0)
        printf("0");
    else
        printf("%d\n",n-ans);
    return 0;
}
