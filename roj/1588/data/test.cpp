#include<fstream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
ifstream cin("a.in");
ofstream cout("data1.in");
int n,m,k,j,i,x,y,t;
int main()
{  srand(time(NULL));//生成随机因子   
   cin>>t;
   //cout<<t<<endl;
   k=20000;
   for(i=1;i<=t;i++)
   {  cout<<rand()%k<<" ";//<<rand()%k<<endl;
      cout<<rand()%k<<rand()%k<<endl;
   }
   return 0;
}
