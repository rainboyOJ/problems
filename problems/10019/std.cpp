#include<bits/stdc++.h>
#define maxn 150005
using namespace std;
struct nod{
	short a,b,c,d,e;
	short tp;	
	short f1,f2,f3,f4,f5;
};
nod arr[maxn];
int tot=0;

int hua(int x) {return (x-1)%4;}
int d(int x) {return (x-1)/4;}
int jie(int x,int y){ return (d(x)+1==d(y)); }

int get2(nod &now)
{
	int tt=hua(now.a);
	if (jie(now.a,now.b) && jie(now.b,now.c) && jie(now.c,now.d) && jie(now.d,now.e))
	if (tt==hua(now.b) && tt==hua(now.c) && tt==hua(now.d) && tt==hua(now.e))
	{
		now.tp=2;
		now.f1=now.a; now.f2=now.b; now.f3=now.c; now.f4=now.d; now.f5=now.e;
		return 1;
	}
	return 0;
}

int get3(nod &now)
{
	if (d(now.b)==d(now.c) && d(now.c)==d(now.d))
	{
		if (d(now.a)==d(now.b))
		{
			now.tp=3;
			now.f1=now.e; now.f2=now.a; now.f3=now.b; now.f4=now.c; now.f5=now.d;
			return 1;		
		}
		if (d(now.d)==d(now.e))
		{
			now.tp=3;
			now.f1=now.a; now.f2=now.b; now.f3=now.c; now.f4=now.d; now.f5=now.e;
			return 1;		
		}
	}
	return 0;
}

int get4(nod &now)
{
	if (d(now.a)==d(now.b) && d(now.d)==d(now.e))
	{
		if (d(now.b)==d(now.c))
		{
			now.tp=4;
			now.f5=now.c; now.f4=now.b; now.f3=now.a; now.f2=now.e; now.f1=now.d;
			return 1;
		}
		if (d(now.c)==d(now.d))
		{
			now.tp=4;
			now.f5=now.e; now.f4=now.d; now.f3=now.c; now.f2=now.b; now.f1=now.a;
			return 1;
		}
	}
	return 0;
}

int get5(nod &now)
{
	int tt=hua(now.a);
	if (hua(now.b)==tt && hua(now.c)==tt && hua(now.d)==tt && hua(now.e)==tt)
	{
		now.tp=5;
		now.f1=now.a; now.f2=now.b; now.f3=now.c; now.f4=now.d; now.f5=now.e;
		return 1;
	}
	return 0;
}

int get6(nod &now)
{
	if (jie(now.a,now.b) && jie(now.b,now.c) && jie(now.c,now.d) && jie(now.d,now.e))
	{
		now.tp=6;
		now.f1=now.a; now.f2=now.b; now.f3=now.c; now.f4=now.d; now.f5=now.e;
		return 1;
	}
	return 0;
} 

int get7(nod &now)
{
	if (d(now.a)==d(now.b) && d(now.b)==d(now.c))
	{
		now.tp=7;
		now.f5=now.c; now.f4=now.b; now.f3=now.a; now.f2=now.e; now.f1=now.d;
		return 1;
	}
	if (d(now.b)==d(now.c) && d(now.c)==d(now.d))
	{
		now.tp=7;
		now.f5=now.d; now.f4=now.c; now.f3=now.b; now.f2=now.e; now.f1=now.a;
		return 1;
	}
	if (d(now.c)==d(now.d) && d(now.d)==d(now.e))
	{
		now.tp=7;
		now.f5=now.e; now.f4=now.d; now.f3=now.c; now.f2=now.b; now.f1=now.a;
		return 1;
	}
	return 0;
}

void work(nod &now)
{
	if (get2(now)) return; if (get3(now)) return; if (get4(now)) return;
	if (get5(now)) return; if (get6(now)) return; if (get7(now)) return;
	return;
}

int cmp(nod x,nod y)
{
	if (x.tp!=y.tp) return x.tp<y.tp;
	if (d(x.f5)!=d(y.f5)) return x.f5>y.f5;
	if (d(x.f4)!=d(y.f4)) return x.f4>y.f4;
	if (d(x.f3)!=d(y.f3)) return x.f3>y.f3;
	if (d(x.f2)!=d(y.f2)) return x.f2>y.f2;
	if (d(x.f1)!=d(y.f1)) return x.f1>y.f1;
	if (hua(x.f5)!=hua(y.f5)) return hua(x.f5)<hua(y.f5);
	if (hua(x.f4)!=hua(y.f4)) return hua(x.f4)<hua(y.f4);
	if (hua(x.f3)!=hua(y.f3)) return hua(x.f3)<hua(y.f3);
	if (hua(x.f2)!=hua(y.f2)) return hua(x.f2)<hua(y.f2);
	return hua(x.f1)<hua(y.f1);
}

int cmp2(nod x,nod y)
{
	if (x.tp!=y.tp) return x.tp<y.tp;
	if (d(x.f5)!=d(y.f5)) return x.f5>y.f5;
	if (d(x.f4)!=d(y.f4)) return x.f4>y.f4;
	if (d(x.f3)!=d(y.f3)) return x.f3>y.f3;
	if (d(x.f2)!=d(y.f2)) return x.f2>y.f2;
	if (d(x.f1)!=d(y.f1)) return x.f1>y.f1;
	return 0;
}

char ch[15]="23456789TJQKA";
char ch2[15]="SHCD"; 
void write(int x) {cout<<ch2[hua(x)]<<ch[d(x)]<<" "; return;}
void out(nod x)
{
	write(x.a); write(x.b); write(x.c); write(x.d); write(x.e);	 cout<<"\n";
	return;
}

int has(int x,int y,int z) {return x*53*53+y*53+z;}
vector<int> a[maxn];

int get()
{
	string s;
	cin>>s;
	int tt=0,qq=0;
	if (s[0]=='S') tt=1; if (s[0]=='H') tt=2; if (s[0]=='C') tt=3; if (s[0]=='D') tt=4;
	if (s[1]>='2' && s[1]<='9') qq=s[1]-'0';
	if (s[1]=='T') qq=10; if (s[1]=='J') qq=11;
	if (s[1]=='Q') qq=12; if (s[1]=='K') qq=13;
	if (s[1]=='A') qq=14;
	return (qq-2)*4+tt; 
}

int main()
{
	ios::sync_with_stdio(false);
	for (int i=1;i<=52;i++)
		for (int j=i+1;j<=52;j++)
		for (int k=j+1;k<=52;k++)
		for (int t=k+1;t<=52;t++)
		for (int q=t+1;q<=52;q++)
		{
			arr[++tot].a=i; arr[tot].b=j; arr[tot].c=k; arr[tot].d=t; arr[tot].e=q;
			work(arr[tot]);
			if (arr[tot].tp==0) tot--;
		}
	sort(arr+1,arr+tot+1,cmp);
	for (int i=1;i<=tot;i++)
	{
		a[has(arr[i].a,arr[i].b,arr[i].c)].push_back(i);
		a[has(arr[i].a,arr[i].b,arr[i].d)].push_back(i);
		a[has(arr[i].a,arr[i].b,arr[i].e)].push_back(i);
		a[has(arr[i].a,arr[i].c,arr[i].d)].push_back(i);
		a[has(arr[i].a,arr[i].c,arr[i].e)].push_back(i);
		a[has(arr[i].a,arr[i].d,arr[i].e)].push_back(i);
		a[has(arr[i].b,arr[i].c,arr[i].d)].push_back(i);
		a[has(arr[i].b,arr[i].c,arr[i].e)].push_back(i);
		a[has(arr[i].b,arr[i].d,arr[i].e)].push_back(i);
		a[has(arr[i].c,arr[i].d,arr[i].e)].push_back(i);
	}
	
	int q;
	int X,Y;
	cin>>q;
	while (q--)
	{
		X=get(); X=X*53+get(); X=X*53+get();
		Y=get(); Y=Y*53+get(); Y=Y*53+get();
		if (cmp2(arr[a[X][0]],arr[a[Y][0]])!=1)
		{
			cout<<-1<<"\n";
			continue;
		}
		int now=0,siz=a[X].size();
		for (int j=1<<12;j>=1;j=j>>1)
		if (now+j<siz && cmp2(arr[a[X][now+j]],arr[a[Y][0]])==1)
			now+=j;
		out(arr[a[X][now]]);
	}
	return 0;
}
