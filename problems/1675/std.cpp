#include <cstdio>
#include <cstring>

int n,k;

int s[10];

int sum = 0;
void dfs(int dep,int sheng){
    if( dep == k){
        if( sheng >= s[dep-1]){
            sum++;
        }
        return ;
    }

    int i;
    for(i=s[dep-1];i<=sheng;i++){
        s[dep]= i;
        dfs(dep+1,sheng-i);
    }
}

int main(){
    scanf("%d%d",&n,&k);
    s[0]=1;
    dfs(1,n);
    printf("%d\n",sum);
    return 0;
}
