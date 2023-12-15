#include <cstdio>

int n;
int dfs(int n,int m){
    if( m > n ) m = n;
    if( m == 1) return 1;
    int ans = 0;
    if( m == n) ans=1,m=n-1;
    for(int i = m ; i>=1;i--){
        int d = dfs(n-i,i);
        ans +=d;
    }
    return ans;
}
int main(){
    scanf("%d",&n);//输入数字
    int ans = dfs(n,n);
    printf("%d\n",ans);
    return 0;
}
