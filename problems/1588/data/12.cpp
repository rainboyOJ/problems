#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long LL;
const int maxn=100+5;

int dp[maxn][105];
int digit[maxn];

int mod,l,r;
int DFS(int pos,int pre,bool limit)
{
    if(pos==-1)
        return pre==0;
    if(!limit&&dp[pos][pre]!=-1)
        return dp[pos][pre];

     LL res=0,end=limit?digit[pos]:9;

     for(int i=0;i<=end;i++)
     {
        int new_pre=(pre+i)%mod;
         res+=DFS(pos-1,new_pre,limit&&i==end);
     }
     if(!limit)
         dp[pos][pre]=res;
    return res;
}

LL solve(int n)
{
     int len=0;
     while(n)
     {
         digit[len++]=n%10;
         n/=10;
     }
     return DFS(len-1,0,true);
}

int main()
{    freopen("data1.in","r",stdin);
     freopen("data1.out","w",stdout);
     while(scanf("%d%d%d",&l,&r,&mod)!=EOF)
     {
         memset(dp,-1,sizeof(dp));
         printf("%lld\n",solve(r)-solve(l-1));
     }
     return 0;
}

