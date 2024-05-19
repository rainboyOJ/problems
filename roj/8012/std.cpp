#include<bits/stdc++.h>
using namespace std;

const int MAXN=100;
long long a[MAXN+5],n,m,sum=0;

int main()
{
    // freopen("gwdml.in","r",stdin);
    // freopen("gwdml.out","w",stdout); 
    cin>>m>>n;
    a[1]=1;
    if (m>n) swap(m,n);
    int t = 1;
    for(int i = 2;i <= 30 ;++i ) // i: 1->30
    {
        t = 2*t;
        a[i] = t + a[i-1];
    }
    cout << a[n] - a[m-1] << endl;
    return 0;
}

