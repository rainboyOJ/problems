#include<iostream>
#include<cmath>
using namespace std;
bool judge(int x);

int main()
{
	int s;
	int i;

	cin>>s;//输入正整数s
	for(i=s/2;i>=2;i--)//和为定值的两个数，越接近，数越大，因此从中间拆分
		if(judge(i)&&judge(s-i))//判断拆分的两个数是否为素数
		{
			cout<<i*(s-i)<<endl;//若是，输出两数积
			break;//终止循环
		}

	return 0;
}
bool judge(int x)//判断素数  
{  
    int i;
	if(x==2)	return false;
    for(i=2;i<=sqrt(x);i++)  
        if(x%i==0)  
            return false;  
    return true;  
}