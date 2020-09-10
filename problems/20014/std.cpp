#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int read() {
    int q=0,w=1;char ch=' ';
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')w=-1,ch=getchar();
    while(ch>='0'&&ch<='9')q=q*10+ch-'0',ch=getchar();
    return q*w;
}
const int N=105;
int T,n,f[N][N][2][N],vis[N][N][2][N];
struct people{int x,e;}p[N];
int dfs(int l,int r,int t,int havego) {
    int& re=f[l][r][t][havego];
    if(vis[l][r][t][havego])return re;
    vis[l][r][t][havego]=1;
    if(l==r) re=max(p[l].e-abs(p[l].x)*(havego+1),-abs(p[l].x)*havego);//送给l处，不送给l处
    else if(!t) {
        re=p[l].e+dfs(l+1,r,0,havego+1)-(p[l+1].x-p[l].x)*(havego+1);//送给l处
        re=max(re,dfs(l+1,r,0,havego)-(p[l+1].x-p[l].x)*havego);//不送给l处
        re=max(re,p[l].e+dfs(l+1,r,1,havego+1)-(p[r].x-p[l].x)*(havego+1));//送给l处
        re=max(re,dfs(l+1,r,1,havego)-(p[r].x-p[l].x)*havego);
    }//不送给l处
    else {
        re=p[r].e+dfs(l,r-1,0,havego+1)-(p[r].x-p[l].x)*(havego+1);//送给r处
        re=max(re,dfs(l,r-1,0,havego)-(p[r].x-p[l].x)*havego);//不送给r处
        re=max(re,p[r].e+dfs(l,r-1,1,havego+1)-(p[r].x-p[r-1].x)*(havego+1));//送给r处
        re=max(re,dfs(l,r-1,1,havego)-(p[r].x-p[r-1].x)*havego);//不送给r处
    }
    return re;
}
int main()
{
    T=1;
    while(T--) {
        n=read();
        for(int i=1;i<=n;++i) p[i].x=read();
        for(int i=1;i<=n;++i) p[i].e=read();
        memset(vis,0,sizeof(vis));
        printf("%d\n",max(dfs(1,n,0,0),dfs(1,n,1,0)));
    }
    return 0;
}
