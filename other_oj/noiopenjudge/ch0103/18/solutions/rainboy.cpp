/* 
 * an = a1 +(n-1)*(a2-a1)
 * */
#include <cstdio>

int main(){
    int a1,a2,n;
    scanf("%d%d",&a1,&a2);
    scanf("%d",&n);
    int ans = a1+(n-1)*(a2-a1);
    printf("%d\n",ans);
    return 0;
}

