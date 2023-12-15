/*
ID:naturec1
PROG: milk4
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#define MEM(a,b) memset(a,b,sizeof(a))
#define REP(i,n) for(int i=0;i<(n);++i)
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define getmid(l,r) ((l) + ((r) - (l)) / 2)
#define MP(a,b) make_pair(a,b)

typedef long long ll;
typedef pair<int,int> pii;
const int INF = (1 << 30) - 1;

int Q,P;
int v[110];
int k;
int cur_p[110];
bool dp[20010];

bool Judge(){
    MEM(dp,false);
    dp[0] = true;
    REP(i,k){
        for(int j = cur_p[i]; j <= Q; ++j)
            dp[j] |= dp[j - cur_p[i]];
    }
    return dp[Q];
}

bool Dfs(int p,int num){
    if(p >= P){
        if(num != k) return false;
        if(Judge()) return true;
        return false;
    }
    cur_p[num] = v[p];
    if(num < k && Dfs(p + 1,num + 1)) return true;
    if(num + P - p - 1 >= k && Dfs(p + 1,num)) return true;
    return false;
}

int main(){
    scanf("%d",&Q);
    scanf("%d",&P);
    REP(i,P) scanf("%d",&v[i]);
    sort(v,v + P);
    for(k = 1; k <= P; ++k){
        if(Dfs(0,0)){
            printf("%d",k);
            REP(i,k) printf(" %d",cur_p[i]);
            puts("");
            break;
        }
    }
    return 0;
}
