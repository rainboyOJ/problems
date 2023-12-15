#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

#define MOD 1000000007
#define LL __int64

int digit[20];
LL power[20];

struct  Node
{
   LL n,s,sq;
}dp[20][10][10];

Node dfs(int pos,int mod,int modSum,bool limit)
{
   if(pos<=0)
   {
      Node t;
      t.n = (mod!=0 && modSum!=0);
      t.s  = t.sq = 0;
      return t;
   }
   if(!limit && dp[pos][mod][modSum].n!=-1) return dp[pos][mod][modSum];
   int end = limit ? digit[pos] : 9;
   Node ans,temp;
   ans.n = ans.s = ans.sq = 0;
   for(int i=0;i<=end;i++)
   {
      if(i == 7) continue;
      temp = dfs(pos-1,(mod*10+i)%7,(modSum+i)%7,limit && (i == end));
      ans.n = (ans.n + temp.n)%MOD;
      ans.s = (ans.s + temp.s + ((i * power[pos])%MOD * temp.n) % MOD) % MOD ;
      ans.sq = (ans.sq + temp.sq + ((2*i*power[pos])%MOD*temp.s)%MOD + (((i*i*power[pos])%MOD*power[pos])%MOD*temp.n)%MOD)%MOD;
   }
   if(!limit) dp[pos][mod][modSum] = ans;
   return ans;
}
LL calc(LL a)
{
   int len = 0;
   while(a>0)
   {
      digit[++len] = a%10;
      a/=10;
   }
   Node ans = dfs(len,0,0,true);
   return ans.sq;
}
void init()
{
   memset(dp,-1,sizeof(dp));
   memset(power,0,sizeof(power));
   power[1] = 1;
   for(int i=2;i<=19;i++)
   {
      power[i] = (power[i-1] * 10)%MOD;
   }
}
int main()
{
   freopen("data1.in","r",stdin);
   freopen("data1.out","w",stdout);
   int t;
   LL l,r;
   init();
   scanf(" %d",&t);
   while(t--)
   {
      scanf(" %I64d %I64d",&l,&r);
      LL ans = (calc(r) - calc(l-1) + MOD)%MOD;
      printf("%lld\n", ans);
   }
   return 0;
}

