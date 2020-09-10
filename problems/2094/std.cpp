/*
PROG:vans
ID:juan1973
LANG:C++
*/
#include<cstdio>
using namespace std;
struct arr{int n,p[1001];}g[1001],f[1001];
int n,i;
arr chen(arr a)
{
  for (int i=1;i<=a.n;i++)
    a.p[i]*=2;
  for (int i=1;i<=a.n;i++)
    if (a.p[i]>9) {a.p[i+1]+=a.p[i]/10;a.p[i]%=10;}
  if (a.p[a.n+1]>0) a.n++;
  return a;
}
arr add(arr a,arr b)
{
  a.n=a.n>b.n?a.n:b.n;
  for (int i=1;i<=a.n;i++)
    a.p[i]+=b.p[i];
  for (int i=1;i<=a.n;i++)
    if (a.p[i]>9) {a.p[i+1]+=a.p[i]/10;a.p[i]%=10;}
  if (a.p[a.n+1]>0) a.n++;
  return a;
}
arr Minus(arr a,arr b)
{
  int i=1,j,k;
  while (i<=b.n)
  {
    if (a.p[i]>=b.p[i])a.p[i]=a.p[i]-b.p[i];
    else
    {
      j=i+1;
      while (a.p[j]==0) j++;
      a.p[j]--;
      for (k=i+1;k<j;k++) a.p[k]=9;
      a.p[i]=a.p[i]+10-b.p[i];
    }
    i++;
  }
  while (a.p[a.n]==0&&a.n>1)a.n--;
  return a;
}
int main()
{
  scanf("%d",&n);
  g[1].p[1]=2;g[2].p[1]=2;g[3].p[1]=8;
  g[1].n=g[2].n=g[3].n=1;
  f[1].p[1]=0;f[2].p[1]=2;f[3].p[1]=4;
  f[1].n=f[2].n=f[3].n=1;
  for (i=4;i<=n;i++)
  {
    g[i]=Minus(add(chen(f[i-1]),add(g[i-1],g[i-2])),g[i-3]);
    f[i]=add(f[i-1],g[i-1]);
  }
  for (i=f[n].n;i>0;i--)
    printf("%d",f[n].p[i]);
  printf("\n");
}
