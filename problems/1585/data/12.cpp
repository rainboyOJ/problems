#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

int f[35][35];
int d[35];
//高度为i(i>=0)时，含有j个1的个数
void init()
{
   memset(f,0,sizeof(f));
   f[0][0] = 1;
   for(int i=1;i<=31;i++)
   {
      f[i][0] = 1;
      for(int j=1;j<=i;j++)
      {
         f[i][j] = f[i-1][j-1] + f[i-1][j];
      }
   }
}
//[0,x]范围内二进制含有k个1的个数
int calc(int x,int k)
{
   //路径上含有的1的个数
   int tot = 0;
   int ans = 0;
   for(int i=31;i>0;i--)
   {
      if(x&(1<<i)) 
      {
         tot++;
         if(tot>k) break;
         x ^= (1<<i);
      }
      if((1<<(i-1))<=x) ans += f[i-1][k-tot];
   }
   if(tot + x == k) ans++;
   return ans;
}
//b进制转化为二进制
int transfer(int b,int x)
{
   int m = 0;
   int ans = 0;
   while(x)
   {
      d[m++] = x % b;
      x/=b;
   }
   for(int i=m-1;i>=0;i--)
   {
      if(d[i]>1) 
      {
         for(int j=i;j>=0;j--) ans |= (1<<j);
      }
      else ans |= d[i]<<i;
   }
   return ans;
}
int main()
{
   freopen("data10.in","r",stdin);
   freopen("data10.out","w",stdout);
   int x,y;
   int k,b;
   init();
   while(scanf(" %d %d",&x,&y)!=EOF)
   {
      scanf(" %d %d",&k,&b);
      x = transfer(b,x-1);
      y = transfer(b,y);
      printf("%d\n",calc(y,k) - calc(x,k));
   }
   return 0;
}
