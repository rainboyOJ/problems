#include<iostream>
using namespace std;

void replace();
int a[1001]={0};
int ans=0;
int m,n;
int x;

int main()
{
	int i;

	cin>>m>>n;
	for(i=1;i<=n;i++)
	{
		cin>>x;//输入单词
		if(a[x]==0&&ans<m)//需要查找且内存未满
		{
			ans++;//查找次数+1
			a[x]=ans;//存储ans，桶排的思想
		}
		else//若内存已满
			replace();//调用函数
	}
	cout<<ans<<endl;
    return 0;
}
void replace()
{
	int sum;
	int i;

	if(a[x]==0&&ans>=m)//需要查找内存已满
	{
		ans++;
		sum=0;
		for(i=0;i<=1000;i++)
		{
			if(a[i]>=1)//每个单词存入顺序向前移动一位
			{
				a[i]=a[i]-1;
				sum++;
			}
			if(sum==m)//移动过后结束循环
				break;
		}
		if(m>0)//若内存非零则存入新单词
			a[x]=m;
	}
}