/*
PROG:rectbarn
ID:juan1973
LANG:C++
*/
#include<stdio.h>  
#include<iostream>  
#include<cstring>
using namespace std;  
const int maxn=3000+5;  
bool a[maxn][maxn];  
int h[2][maxn],l[2][maxn],r[2][maxn],tl[maxn],tr[maxn];  
int n,m,i,j,ans,temp,x,y,p,now;  
int main()  
{  
  scanf("%ld%ld%ld",&n,&m,&p);  
  memset(a,1,sizeof(a));
  for (i=1;i<=p;i++)  
  {  
    scanf("%ld%ld",&x,&y);
    a[x][y]=false;
  }  
  for (j=1;j<=m;j++)
    if (a[1][j]) h[1][j]=1;else h[1][j]=0;
  l[1][1]=1;
  for (j=2;j<=m;j++)   
    if (a[1][j])   
      {  
        if (!a[1][j-1]) l[1][j]=j;  
        else l[1][j]=l[1][j-1];  
      }  
      else {l[1][j]=1;r[1][j]=m;}
  r[1][m]=m;
  for (j=m-1;j>0;j--)  
    if (a[1][j])  
      {  
        if (!a[1][j+1]) r[1][j]=j;  
        else r[1][j]=r[1][j+1];  
      }  
  now=1;
  for (i=2;i<=n;i++)  
  {  
    now^=1;
    for (j=1;j<=m;j++)
      if (a[i][j]) {h[now][j]=h[now^1][j]+1;} 
      else {l[now][j]=1;r[now][j]=m;h[now][j]=0;}
    for (j=1;j<=m;j++)   
      if (a[i][j])   
      {  
        if (tl[j-1]==0) tl[j]=j;  
        else tl[j]=tl[j-1];  
      }  
     else tl[j]=0;
    for (j=m;j>0;j--)  
      if (a[i][j])  
      {  
        if (tr[j+1]==0) tr[j]=j;  
        else tr[j]=tr[j+1];  
      }  
      else tr[j]=0;  
    for (j=1;j<=m;j++)  
      if (a[i][j])  
      {  
        l[now][j]=max(l[now^1][j],tl[j]);  
        r[now][j]=min(r[now^1][j],tr[j]);  
        temp=h[now][j]*(r[now][j]-l[now][j]+1);  
        if (temp>ans)   
          ans=temp;  
      }    
  }  
  
  printf("%ld\n",ans);  
  return 0;  
}
