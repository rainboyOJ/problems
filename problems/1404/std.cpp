#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int n,home,x;
	int i;

	cin>>n;//输入n

	/*
		设最后门牌号为k，则总和为：k*(k+1)/2
		设家的门牌号为x，则由题意：k*(k+1)/2=3*x+n
		即：k*(k+1)=6*x+2*n
		又：k*(k+1)+k+1>6*x+2*n
		得：(k+1)*(k+1)>6*x+2*n
		开方：k+1>sqrt(6*x+2*n)
		两边减一：k>sqrt(6*x+2*n)-1
		x取最小值1：home=sqrt(6+2*n)-1
	*/

	home=sqrt(6+2*n)-1;
	for(i=home;;i++)//从家的门牌号开始逐个尝试
	{
		if((i*i+i-2*n)%6==0)
		{
			x=(i*i+i-2*n)/6;
			if(x<=0)	continue;//x不可能<1
			if(x>0)//找到后
			{
				cout<<x<<" "<<i;//输出
				break;//终止循环
			}
		}
	}
	return 0;
}