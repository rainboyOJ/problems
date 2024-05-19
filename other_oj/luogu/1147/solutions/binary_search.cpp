#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<set>
using namespace std;
const int maxn=2000000 + 5;
long long a[maxn];

int main()
{
    long long n;
    cin>>n;
    for(int i=1;i<=n;i++) a[i]=a[i-1]+i;//前缀和
    for(int i=1;i<=n;i++)
    {
        long long mid=a[i-1]+n;// 要找的那个数,显然比a[i-1] 大n
        long long pos=lower_bound(a,a+n+1,mid)-a; // 找到第一个>=的位置
        if(a[pos]-a[i-1]==n)  //确实为n
        {
            if(i!=pos) //不止一个数
                cout<<i<<" "<<pos<<endl;
        }
    }
    return 0;
}

