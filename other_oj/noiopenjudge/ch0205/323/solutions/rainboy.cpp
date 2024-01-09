/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 02月 26日 星期六 14:54:21 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

char mg[10][10];

bool hang[10],lie[10];
int ans = 0;

bool is_in(int x,int y){
    if( lie[y] == 0)
        return 1;
    return 0;
}

void Set(int x,int y){
    lie[y] = 1;
}

void unSet(int x,int y){
    lie[y] = 0;
}

void dfs(int x,int cnt){
    if( x > n ){
        if( cnt == 0) ans++;
        return;
    }
    dfs(x+1,cnt); //不放
    for(int i=1;i<=n;++i){
        if( mg[x][i] == '.') continue;
        if( is_in(x,i)){
            Set(x,i);
            dfs(x+1,cnt-1);
            unSet(x, i);
        }
    }

}

int main(int argc,char * argv[]){
    while ( 1 ) {
        scanf("%d%d",&n,&m);
        if( n == -1 && m == -1) return 0;
        for(int i=1;i<=n;++i){
            scanf("%s",&mg[i][1]);
        }
        ans = 0;
        memset(lie,0,sizeof(lie));
        dfs(1,m);
        printf("%d\n",ans);
    }
    return 0;
}
