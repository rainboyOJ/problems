#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=40000;
struct Edge{
	int end; Edge* next; Edge* head;
	Edge() { head=NULL; }
	void Insert(const int &end1){
		Edge *p=new Edge;  p->next=head;
		head=p;    p->end=end1;  
	}
}edge[MAXN];
int n,son[MAXN],fa[MAXN],dep[MAXN],mark[MAXN],top[MAXN];

namespace Nsolve{
	
	int fmax[MAXN*4],fsum[MAXN*4];
	
	int max(const int &x, const int &y){ return x>y?x:y; }
	
	void swap(int &x,int &y){
		int t=x;  x=y;  y=t;
	}

	void Insert(const int &k,const int &m,const int &n,const int &x,const int &value){
		if ((m>x) || (x>n)) return ;
		if (m==n) {fsum[k]=fmax[k]=value; return ;}
		int z1=k<<1,z2=(k<<1)+1,mid=(m+n)>>1;
		Insert(z1,m,mid,x,value);    Insert(z2,mid+1,n,x,value);
		fmax[k]=max(fmax[z1],fmax[z2]);
		fsum[k]=fsum[z1]+fsum[z2];
	}
	
	int Answer_max(const int &k,const int &m,const int &n,const int &x,const int &y){
		if ((y<m) || (x>n)) return -1000000000;
		if ((x<=m) && (n<=y)) return fmax[k];
		int z1=k<<1,z2=(k<<1)+1,mid=(m+n)>>1;
		return max(Answer_max(z1,m,mid,x,y),Answer_max(z2,mid+1,n,x,y));
	}

	int Answer_sum(const int &k,const int &m,const int &n,const int &x,const int &y){
		if ((y<m) ||(x>n)) return 0;
		if ((x<=m) && (n<=y)) return fsum[k];
		int z1=k<<1,z2=(k<<1)+1,mid=(m+n)>>1;
		return Answer_sum(z1,m,mid,x,y)+Answer_sum(z2,mid+1,n,x,y);
	}	

	int Find_max(int x,int y){ 
		if (top[x]!=top[y]){
			if (dep[top[y]]>dep[top[x]]) swap(x,y);
			return max(Find_max(fa[top[x]],y),Answer_max(1,1,n,mark[top[x]],mark[x]));
		}
		if (dep[y]<dep[x]) swap(x,y);
		return Answer_max(1,1,n,mark[x],mark[y]);
	}

        int Find_sum(int x,int y){
		if (top[x]!=top[y]){
			if (dep[top[y]]>dep[top[x]]) swap(x,y);
			return Find_sum(fa[top[x]],y)+Answer_sum(1,1,n,mark[top[x]],mark[x]);
		}
		if (dep[y]<dep[x]) swap(x,y);
		return Answer_sum(1,1,n,mark[x],mark[y]);
	}

	void Solve(){
		int m;
		char ch;
		scanf("%d",&m);
		for (int i=0; i<m; ++i){
			while (ch=getchar(),(ch!='C')&& (ch!='Q'));
			int x,y;  
			if (ch=='C'){
				scanf("HANGE%d%d",&x,&y);
				Insert(1,1,n,mark[x],y);
				continue;
			}
			ch=getchar();
			if (ch=='M') {  
				scanf("AX%d%d",&x,&y);
				printf("%d\n",Find_max(x,y));
				continue;
			} 
			scanf("UM%d%d",&x,&y);
			printf("%d\n",Find_sum(x,y));
		}
	}
}

namespace Ninit{
	
	int sum[MAXN],tot=1;
	void Dfs1(const int &x,const int &father){
		sum[x]=1;   fa[x]=father;  dep[x]=dep[father]+1;
		for (Edge* k=edge[x].head; k!=NULL; k=k->next){
			int l=k->end;
			if (l==father) continue;
			Dfs1(l,x);        sum[x]+=sum[l];
			if (sum[l]>sum[son[x]]) son[x]=l;
		}
	}
	
	void Dfs2(const int &x,const int &father){ 
		if (son[x]) { mark[son[x]]=++tot; top[son[x]]=top[x];  Dfs2(son[x],x);}	
		for (Edge* k=edge[x].head; k!=NULL; k=k->next){
			int l=k->end;
			if (top[l]) continue;
			mark[l]=++tot;  top[l]=l;
			Dfs2(l,x);
		}
	}

	void Init(){
		scanf("%d",&n);
		for (int i=1; i<n; ++i){
			int x,y;
			scanf("%d%d",&x,&y);
			edge[x].Insert(y);
			edge[y].Insert(x);
		}
		memset(son,0,sizeof(son));
		memset(sum,0,sizeof(sum));
		memset(dep,0,sizeof(dep));
		Dfs1(1,0);     top[1]=mark[1]=1;  
		Dfs2(1,0);     
		for (int i=1; i<=n; ++i){
			int x;  scanf("%d",&x);
			Nsolve::Insert(1,1,n,mark[i],x);
		}
	}
}

int main(){
	Ninit::Init();
	Nsolve::Solve();
}
