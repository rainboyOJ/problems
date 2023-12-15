#include <cstdio>
#include <cstring>
using namespace std;
const int MAXM=60;
int a[MAXM],b[MAXM],sum[MAXM],n,m,c;
int f[MAXM][MAXM][2];
int min(int a,int b)//这一点希望大家注意：最好max和min函数自己写，会有效的加快程序速度
{return a<b?a:b;}
int max(int a,int b)
{return a>b?a:b;}
int main()
{
  scanf("%d%d",&n,&c);
  memset(f,127,sizeof(f));//赋成极大值防止后面的min出问题
  for(int i=1;i<=n;i++)
    scanf("%d%d",&a[i],&b[i]),sum[i]=sum[i-1]+b[i];
  f[c][c][0]=f[c][c][1]=0;//瞬间被关（初始化）
  for(int l=2;l<=n;l++)
    for(int i=1;i+l-1<=n;i++)
      {
    int j=i+l-1;
    f[i][j][0]=min(f[i+1][j][0]+(a[i+1]-a[i])*(sum[i]+sum[n]-sum[j]),//继续走下去会更快吗？
               f[i+1][j][1]+(a[j]-a[i])*(sum[i]+sum[n]-sum[j]));//还是从j点折返回来会更快？（此时假设[i+1][j]被关，i亮，从j端点往回赶去关i）
//要注意的一点是sum[n]-(sum[j]-sum[i])是包括了i这一点的电能的，因为走过来的过程中灯i也会耗电
    f[i][j][1]=min(f[i][j-1][0]+(a[j]-a[i])*(sum[i-1]+sum[n]-sum[j-1]),//同上
               f[i][j-1][1]+(a[j]-a[j-1])*(sum[i-1]+sum[n]-sum[j-1]));
        }
  int ans=min(f[1][n][0],f[1][n][1]);
  printf("%d",ans);
  return 0;
}
