/* 
 * 先找到环上的最小编号的点,然后从这个点开始
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int n;
int a[200005];
bool vis[200005] = {0}; //是否已经访问过
int dnf[200005];
bool isRn[200005] = {0}; //是不是最小反回点
int maxRn[200005] = {0}; //最小反回点的最大接触值

int ans = 0x7f7f7f7f;

void dfs(int x,int idx){
    vis[x] = 1; //已经访问
    dnf[x] =idx;
    
    int next = a[x];

    if( vis[next] == 0) { //没有访问过
        dfs(next,idx+1);
    }
    else { //已经访问过
        isRn[next] = 1;
        maxRn[next] = x;
    }
    //回溯
    if( isRn[x])
        ans = min(ans,dnf[maxRn[x]] -dnf[x]  +1);
}

int main(){
    scanf("%d",&n);
    int i;
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(i=1;i<=n;i++)
        if( vis[i] == 0)
            dfs(i,1);
    printf("%d",ans);

    return 0;
}


