#include<bits/stdc++.h>
using namespace std;
struct node{
    int to,nxt;
}e[1000005];
int n,m,head[100005],tot,ans[200005],zans;
void build(int a,int b)
{
    e[++tot].to=b;
    e[tot].nxt=head[a];
    head[a]=tot;
}
int z[1000005],zz;
int main()
{
    scanf("%d%d",&n,&m);
    for(int a,b,i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        build(a,b);
        build(b,a);
    }
    z[++zz]=1;
    int p;
    while(zz>0)
    {
        p=z[zz];
        int i=head[p];
        if(i)
        {
            z[++zz]=e[i].to;
            head[p]=e[i].nxt;
        }
        else
        {
            --zz;
            ans[++zans]=p;
        }
    }
    for(int i=zans;i;i--)
    {
        printf("%d\n",ans[i]);
    }
}
