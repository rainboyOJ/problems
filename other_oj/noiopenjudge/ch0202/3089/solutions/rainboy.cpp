#include <cstdio>

int fab(int n){
    if( n== 0 || n == 1)
        return 1;
    return fab(n-1)+fab(n-2);
}
int main(){
    int t;
    while(scanf("%d",&t) != EOF){
        int ans = fab(t);
        printf("%d\n",ans);
    }
    return 0;
}
