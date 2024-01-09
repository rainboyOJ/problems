#include <cstdio>

int main(){
    int n,x,y;
    scanf("%d%d%d",&n,&x,&y);
    int ans = y / x;
    if( y % x != 0)
        ans++;
    printf("%d",n-ans);
    return 0;
}

