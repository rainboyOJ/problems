/*
PROG:picture
ID:juan1973
LANG:C++
*/
#include<stdio.h>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=5005;
const int size=20005;
const int zero=10000;
struct node{int x,y,f;bool ok;}a[2][maxn*2];
int level[size];
int n,i,x1,x2,y1,y2,ans;
bool cmp(node c,node d){return c.f<d.f||c.f==d.f&&c.ok;}
void find(int o)
{
  sort(a[o]+1,a[o]+n+1,cmp);
  memset(level,0,sizeof(level));
  int j;
  for (int i=1;i<=n;i++)
  {
    if (a[o][i].ok) 
    {
      for (j=a[o][i].x;j<a[o][i].y;j++)
      {
        level[j]++;
        if (level[j]==1) ans++;
      }
    }
    else
    {
      for (j=a[o][i].x;j<a[o][i].y;j++)
      {
        level[j]--;
        if (level[j]==0) ans++;
      }
    }
  }
}
int main()
{
  scanf("%d",&n);
  for (i=1;i<=n;i++)
  {
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    x1+=zero;x2+=zero;y1+=zero;y2+=zero;
    a[0][i*2-1].x=x1;a[0][i*2-1].y=x2;a[0][i*2-1].ok=true;a[0][i*2-1].f=y1;
    a[0][i*2].x=x1;a[0][i*2].y=x2;a[0][i*2].ok=false;a[0][i*2].f=y2;
    a[1][i*2-1].x=y1;a[1][i*2-1].y=y2;a[1][i*2-1].ok=true;a[1][i*2-1].f=x1;
    a[1][i*2].x=y1;a[1][i*2].y=y2;a[1][i*2].ok=false;a[1][i*2].f=x2;
  }
  n=n*2;
  find(0);
  find(1);
  printf("%d\n",ans);
  return 0;
}
