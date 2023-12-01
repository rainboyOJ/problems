#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
using namespace std;
const int N = 8;
//Use 3 binary bits to donate the relation between 12 , 13 or 23,
//like 3=011 means 1<2,1>3,2>3, which is permutation (2 1 3)
//so 0,1,3,4,6,7 all donate permutations
const bool valid[N]={1,1,0,1,1,0,1,1};	//0,1,3,4,6,7donate permutations, their valid is 1

int val[N][N];	//when voter1 choose i, voter2 choose j, then the welfare permutation is val[i][j]
long long ans=0;
int m;



void Judge()	//Judge if it's Non-dictatorship. If it is, then it's an answer
{
	int i,j;
	bool d;
	d=1;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(!valid[i] || !valid[j])
				continue;
			if(val[i][j]!=i)	//if the first voter is dictatorship
				d=0;
		}
	}
	if(d && m==5)
		return;
	d=1;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(!valid[i] || !valid[j])
				continue;
			if(val[i][j]!=j)	//if the second voter is dictatorship
				d=0;
		}
	}
	if(d && m==5)
		return;
	ans++;
	//If exist, ans count the number
}


void dfs(int x,int y)	//decide val[i][j] one by one
{
	if(x>=N)
	{
		Judge();
		return;
	}
	int tx=x,ty=y+1;
	if(ty>=N)
	{
		tx++;
		ty=0;
	}
	//tx,ty means the next (i,j) to decide
	if(!valid[x] || !valid[y])
	{
		dfs(tx,ty);
		return;
	}
	int i,j,k;
	for(i=0;i<N;i++)
	{
		if(valid[i])
		{
			val[x][y]=i;
			int t=(x^y^7);	//the bits that same for two voters
			if(m>3 && (x&t)!=(val[x][y]&t))	//Non-Unanimity 
				continue;
			//Here, start to judge IIA
			bool can=1;
			for(j=0;j<=x;j++)
			{
				for(k=0;k<N;k++)
				{
					if(!valid[j] || !valid[k])
						continue;
					if(j==x && k==y)
						break;
					int a=(((x^j^7)&(y^k^7)));//the bits that should same
					int b=(val[j][k]^val[x][y]^7);//the bits that same
					if(a!=(a&b))
						can=0;
				}
			}
			if(can)
				dfs(tx,ty);
		}
	}
}

void dfs2(int x,int y)
{
	if(x>=N)
	{
		Judge();
		return;
	}
	int tx=x,ty=y+1;
	if(ty>=N)
	{
		tx++;
		ty=0;
	}
	//tx,ty means the next (i,j) to decide
	if(!valid[x] || !valid[y])
	{
		dfs2(tx,ty);
		return;
	}
	int i,j,k;
	int tv=0;
	for(i=0;i<N;i++)
	{
		if(valid[i])
		{
			val[x][y]=i;
			int t=(x^y^7);	//the bits that same for two voters
			if(!((x&t)!=(val[x][y]&t)))	//Unanimity 
				tv++;
		}
	}
	//printf("%d\n",tv);
	ans*=tv;
	dfs2(tx,ty);
}

int main()
{
	freopen("vote.in","r",stdin);
	freopen("vote.out","w",stdout);
	cin>>m;
	if(m==1)
		printf("10314424798490535546171949056\n");	//6^{36}
	else if(m==2)
	{
		ans=1;
		dfs2(0,0);
		cout<<ans<<endl;
	}
	else
	{
		dfs(0,0);
		cout<<ans<<endl;
	}
	return 0;
}
