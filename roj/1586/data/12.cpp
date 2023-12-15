#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define LL long long

const int N=25;
int digit[N];
LL dp[N][N];

LL dfs(int pos,int statu,int limit)
{
     int i,end,s;
     LL res=0;
     if(pos==-1)
        return 1;
     if(!limit&&dp[pos][statu]!=-1)
        return dp[pos][statu];

     end=limit?digit[pos]:9;
     for(i=statu;i<=end;i++)
         res+=dfs(pos-1,i,limit&&i==end);
     if(!limit)
         dp[pos][statu]=res;
    return res;
}

LL calc(LL n)
{
     int len=0;
     memset(dp,-1,sizeof(dp));
     while(n)
     {
         digit[len++]=n%10;
         n/=10;
     }
     return dfs(len-1,0,1);
}

int main()
{    freopen("data1.in","r",stdin);
     freopen("data1.out","w",stdout);
     LL a,b;
     while(scanf("%lld %lld",&a,&b)!=EOF)
         printf("%lld\n",calc(b)-calc(a-1));
    return 0;
}

