#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
int n,a[MAXN],limit,pre,ans,List[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    limit=pre=1;
    for(int i=1;i<=n+1;++i)
    {
        if(limit<i){
            List[++ans]=pre;
            pre=limit=i;
        }
        if(i+a[i]>limit){
            limit=i+a[i];
            pre=i;
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<=ans;++i){
        printf("%d%c",List[i],i==n?'\n':' ');
    }
    return 0;
}
