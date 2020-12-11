#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e4+1;
int x[N],y[N];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
            scanf("%d%d",&x[i],&y[i]);
    }
    sort(x+1,x+1+n);
    sort(y+1,y+1+n);
    for(int i=1;i<=n;i++)x[i]-=i;
    sort(x+1,x+1+n);
    int ans=0;
    for(int i=1;i<=n/2;i++){
        ans+=x[n-i+1]-x[i]+y[n-i+1]-y[i];
    }
    cout<<ans<<'\n';
}
