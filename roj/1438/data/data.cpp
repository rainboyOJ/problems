#include<fstream>
#include<cmath>
using namespace std;
ifstream cin("a.in");
ofstream cout("data4.in");
int T,n,k,j,i,x,y,z;
int main()
{  srand(time(NULL));//生成随机因子   
   cin>>T;
   cout<<T<<endl; n=1000;double m=0.1;
   for(int i=1;i<=T;i++)
   {  x=rand()%n+1;y=rand()%n+1;z=rand()%n+1;
      cout<<(x+y)*m<<" "<<y*m<<" "<<z*0.1<<endl;
   }
   //system("pause"); 
}
