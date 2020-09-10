#include<iostream>  
#include<cstring>  
#include<cmath>  
#include<cstdio>  
#include<algorithm>  
using namespace std;  
typedef long long ll;  
  
ll exgcd(ll m,ll& x,ll n,ll& y)  
{  
    ll x1,y1,x0,y0;  
    x0=1;y0=0;  
    x1=0;y1=1;  
    ll r=(m%n+n)%n;  
    ll q=(m-r)/n;  
    x=0;y=1;  
    while(r)  
    {  
        x=x0-q*x1;y=y0-q*y1;  
        x0=x1;y0=y1;  
        x1=x;y1=y;  
        m=n;n=r;r=m%n;  
        q=(m-r)/n;  
    }  
    return n;  
}  
  
int main()  
{  
	freopen("data10.in","r",stdin);
	freopen("data10.out","w",stdout);
    int t;  
    cin>>t;  
    while(t--)  
    {  
        ll n,d,x,y,a,b;  
        cin>>n>>d>>x>>y;  
        ll g=exgcd(d,a,n,b);  
        if((x-y)%g!=0) cout<<"Impossible"<<endl;  
        else{  
            ll s=n/g;  
            a=a*(y-x)/g;  
            a=(a%s+n)%s;  
            cout<<a<<endl;  
        }  
          
    }  
}  
