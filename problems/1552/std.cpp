#include<iostream>  
#include<algorithm>  
#include<cstdio>  
#include<cstdlib>  
using namespace std;  
const int ONE=100005;  
int n,Q;  
int x,y;  
int next[ONE*2],first[ONE*2],go[ONE*2],tot;  
int Dep[ONE];  
int f[ONE][21];  
int Add(int u,int v)               //连边
{  
    next[++tot]=first[u]; first[u]=tot; go[tot]=v;  
    next[++tot]=first[v]; first[v]=tot; go[tot]=u;  
}  
void Deal_first(int u,int father)     //预处理 
{  
    Dep[u]=Dep[father]+1;  
    for(int i=0;i<=19;i++)  
    {  
        f[u][i+1]=f[f[u][i]][i];  
    }  
    for(int e=first[u];e;e=next[e])  
    {  
        int v=go[e];  
        if(v==father) continue;  
        f[v][0]=u;  
        Deal_first(v,u);  
    }  
}  
int LCA(int x,int y)              //找lca
{  
    if(Dep[x]<Dep[y]) swap(x,y);  
    for(int i=20;i>=0;i--)  
    {  
        if(Dep[f[x][i]]>=Dep[y]) x=f[x][i];  
        if(x==y) return x;  
    }  
    for(int i=20;i>=0;i--)  
    {  
        if(f[x][i]!=f[y][i])  
        {  
            x=f[x][i];  
            y=f[y][i];  
        }  
    }  
    return f[x][0];  
}  
int dist(int x,int y)               //求距离
{  
    return Dep[x]+Dep[y]-2*Dep[LCA(x,y)];  
}  
int main()  
{  
	freopen("test10.in","r",stdin);
	freopen("test10.out","w",stdout);
    cin>>n;  
    for(int i=1;i<n;i++)  
    {  
        scanf("%d%d",&x,&y);  
        Add(x,y);  
    }  
    Deal_first(1,0);  
    cin>>Q;  
    while(Q--)  
    {  
        scanf("%d%d",&x,&y);  
        printf("%d\n",dist(x,y));  
    }  
}  
