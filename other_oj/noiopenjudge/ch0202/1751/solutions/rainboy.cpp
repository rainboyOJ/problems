#include <cstdio>
#include <cmath>
int n;
int cnt = 0;
void dfs(int f,int a){
    int i,end= (int)sqrt(a);
    for(i=f;i<=end;i++){
        if( a % i ==0){
            int ret = a / i;
            if ( ret >= i){
                cnt++;
                dfs(i,ret);
            }
        }
    }
}
int main(){
    int i,t;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        scanf("%d",&t);
        cnt = 0;
        dfs(2,t);
        printf("%d\n",cnt+1);
    }
    return 0;
}
