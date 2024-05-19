#include<iostream>
using namespace std;
typedef long long ll;
ll x,y,len; int k;

void print(ll a,ll b,ll c) {
    cout << a << " ";
    cout << b << " ";
    cout << c << "\n";
}

ll fun(int k)
{
    ll sum=1;
    for(int i=1;i<=k;++i) sum*=2;
    return sum;
}
void solve(ll x,ll y,ll a,ll b,ll l)
{
    if(l==1) return;
    if(x-a<=l/2-1 && y-b<=l/2-1)
    {
        print(a+l/2,b+l/2,1);
        solve(x,y,a,b,l/2);
        solve(a+l/2-1,b+l/2,a,b+l/2,l/2);
        solve(a+l/2,b+l/2-1,a+l/2,b,l/2);
        solve(a+l/2,b+l/2,a+l/2,b+l/2,l/2);
    }
    else if(x-a<=l/2-1 && y-b>l/2-1)
    {
        print(a+l/2,b+l/2-1,2);
        solve(a+l/2-1,b+l/2-1,a,b,l/2);
        solve(x,y,a,b+l/2,l/2);
        solve(a+l/2,b+l/2-1,a+l/2,b,l/2);
        solve(a+l/2,b+l/2,a+l/2,b+l/2,l/2);
    }
    else if(x-a>l/2-1 && y-b<=l/2-1)
    {
        print(a+l/2-1,b+l/2,3);
        solve(a+l/2-1,b+l/2-1,a,b,l/2);
        solve(a+l/2-1,b+l/2,a,b+l/2,l/2);
        solve(x,y,a+l/2,b,l/2);
        solve(a+l/2,b+l/2,a+l/2,b+l/2,l/2);
    }
    else
    {
        print(a+l/2-1,b+l/2-1,4);
        solve(a+l/2-1,b+l/2-1,a,b,l/2);
        solve(a+l/2-1,b+l/2,a,b+l/2,l/2);
        solve(a+l/2,b+l/2-1,a+l/2,b,l/2);
        solve(x,y,a+l/2,b+l/2,l/2);
    }
}
int main()
{
    cin >> k >> x >> y;
    len=fun(k);
    solve(x,y,1,1,len);
    return 0;
}


