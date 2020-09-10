#include<fstream>
#include<cmath>
using namespace std;
ifstream cin("a.in");
ofstream cout("data6.in");
int n,m,k,j,i,x,y,z,r;
int main()
{  srand(time(NULL));//生成随机因子
   cin>>n;cout<<5<<endl;
   for(k=1;k<=5;k++)
   {   x=rand()%2000+10;y=rand()%20+1;
       cout<<n<<" "<<x<<" "<<y<<endl;
       for(int i=1;i<=n;i++)
       {  z=rand()%x+1;r=rand()%22+1;
          cout<<z<<" "<<r<<endl;
       }
   }
   cout<<endl;
   //system("pause");  
}
