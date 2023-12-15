#include<fstream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
ifstream cin("a.in");
ofstream cout("data10.in");
int n,m,k,j,i,x,y,t;
int main()
{  srand(time(NULL));//生成随机因子   
   cin>>t;
   k=10000;
   while(1)
   {  x=rand()%k;
      y=rand()%k;
      n=rand()%20+1;m=rand()%10+1;
      if(x<=y){cout<<x<<" "<<y<<endl;cout<<n<<" "<<m<<endl;break;}
   }
   return 0;
}
