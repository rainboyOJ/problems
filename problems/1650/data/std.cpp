#include<iostream>  
#include<cstring>  
#include<cmath>  
#include<cstdio>  
#include<algorithm>  
using namespace std;  
long long n,m,p;  
long long KSM(long long a,long long b)  
{  long long s=1;  
   while(b)  
   {  if(b&1)s=s*a%p;  
      a=a*a%p;  
      b>>=1;  
   }  
   return s;  
}  
long long C(long long n,long long m)  
{  if(m>n)return 0;  
   long long a=1,b=1;  
   for(long long i=n-m+1;i<=n;i++)a=a*i%p;  
   for(long long i=2;i<=m;i++)b=b*i%p;  
   return a*KSM(b,p-2)%p;  
}  
long long Lucas(long long n,long long m)  
{  int i,j;  
   if(!m)return 1;  
     else return (C(n%p,m%p)*Lucas(n/p,m/p))%p;  
}  
int main()  
{  
	freopen("data10.in","r",stdin);
	freopen("data10.out","w",stdout);
	int i,j,k,T;  
   cin>>T;  
   while(T--)  
   {  cin>>n>>m>>p;  
      cout<<Lucas(n,m)<<endl;  
   }  
   return 0;  
}  
