#include<string.h>
#include<stdio.h>
#include<algorithm>
#define MAXN 2100000
using namespace std;
class DC3{
	public:
		char* ch;
		int *rank,*SA;
		int n;
		int cnt0,cnt1,cnt2;
		static int sum[MAXN];
		static int tmpSA[MAXN];
		static int tmpRank[MAXN];
		DC3(){}
		DC3(int* _rank,int* _SA,int _n,char* s=NULL){
			rank=_rank;
			SA=_SA;
			n=_n;
			rank[n]=rank[n+1]=-1;
			if(s==NULL) return;
			for(int i=0;i<n;i++)
				rank[i]=s[i];
			ch=s;
		}
		void getH(int* h){
			for(int i=0;i<n;i++){
				if(rank[i]==0){
					h[i]=0;
				}
				else {
					h[i]=(i?max(0,h[i-1]-1):0);
					for(;h[i]<n&&ch[i+h[i]]==ch[SA[rank[i]-1]+h[i]];h[i]++);
				}
			}
		}
		void radixSort(int* rank,int* SA,int n){
			int maxKey=0;
			for(int i=0;i<n;i++){
				sum[rank[SA[i]]+2]++;
				maxKey=max(maxKey,rank[SA[i]]+2);
			}
			for(int i=1;i<=maxKey+1;i++)
				sum[i]+=sum[i-1];
			for(int i=0;i<n;i++){
				tmpSA[sum[rank[SA[i]]+1]++] = SA[i];
			}
			memcpy(SA,tmpSA,sizeof(int)*n);
			memset(sum,0,sizeof(int)*(maxKey+2));
		}
		int convert(int x){
			if(x<cnt1)return x*3+1;
			return (x-cnt1-1)*3+2;
		}
		int co_convert(int x){
			if(x%3==1)return x/3;
			return x/3+cnt1+1;
		}
		bool compare(int i,int j,int* nextRank){
			if(rank[i]!=rank[j])return rank[i]<rank[j];
			if(i%3+j%3==3)return nextRank[co_convert(i)]<nextRank[co_convert(j)];
			return compare(i+1,j+1,nextRank);
		}
		bool operator ()(int a,int b){
			if(a==b)return false;
			while(rank[a]==rank[b])++a,++b;
			return rank[a]<rank[b];
		}
		void solve(){
			for(int i=0;i<n;i++)
				SA[i]=i;
			if(n<=100){
				sort(SA,SA+n,*this);
				for(int i=0;i<n;i++)
					rank[SA[i]]=i;
				return;
			}
			radixSort(rank+2,SA,n);
			radixSort(rank+1,SA,n);
			radixSort(rank,SA,n);
			tmpRank[SA[0]]=0;
			for(int i=1;i<n;i++)
				tmpRank[SA[i]]=tmpRank[SA[i-1]]+
					(rank[SA[i]]!=rank[SA[i-1]]||
					 rank[SA[i]+1]!=rank[SA[i-1]+1]||
					 rank[SA[i]+2]!=rank[SA[i-1]+2]);
			memcpy(rank,tmpRank,sizeof(int)*n);
			if(rank[SA[n-1]]==n-1)return;
			int* nextRank=rank+n+2;
			int nextN=0;
			cnt1=cnt2=0;
			for(int i=1;i<n;i+=3){
				nextRank[nextN++]=rank[i]+1;
				cnt1++;
			}
			nextRank[nextN++]=0;
			for(int i=2;i<n;i+=3){
				nextRank[nextN++]=rank[i]+1;
				cnt2++;
			}
			cnt0=n-cnt1-cnt2;
			int* nextSA=SA+n;
			DC3 next(nextRank,nextSA,nextN);
			next.solve();
			for(int i=0;i<nextN;i++){
				if(nextRank[i]==0)continue;
				tmpRank[convert(i)]=nextRank[i];
			}
			for(int i=0;i<n;i+=3)
				SA[i/3]=i;
			radixSort(tmpRank+1,SA,cnt0);
			radixSort(rank,SA,cnt0);
			memcpy(tmpSA,SA,sizeof(int)*cnt0);
			for(int i=1,j=0,cnt=0;i<=nextN;i++){
				while(j<cnt0&&(i==nextN||compare(tmpSA[j],convert(nextSA[i]),nextRank))){
					SA[cnt++]=tmpSA[j++];
				}
				SA[cnt++]=convert(nextSA[i]);
			}
			for(int i=0;i<n;i++)
				rank[SA[i]]=i;
		}
};
int DC3::sum[MAXN]={};
int DC3::tmpSA[MAXN];
int DC3::tmpRank[MAXN];

int rank[3*MAXN],SA[3*MAXN],h[MAXN];
char ch[MAXN];

int st[MAXN];
int len[MAXN];
int half[MAXN];
int rmq[MAXN][20];
void build_rmq(int L){
	half[0]=0;
	for(int i=1;i<=L;i++){
		half[i]=half[i-1];
		if((2<<half[i])==i)half[i]++;
	}
	for(int i=0;i<L;i++){
		rmq[i][0]=h[SA[i]];
	}
	for(int r=1;r<20;r++){
		for(int i=0;i+(1<<r)<=L;i++)
			rmq[i][r]=min(rmq[i][r-1],rmq[i+(1<<(r-1))][r-1]);
	}
}
int query(int fr,int to){
	if(fr==to)return 987654321;
	int L=half[to-fr];
	fr++;
	return min(rmq[fr][L],rmq[to-(1<<L)+1][L]);
}
int main(){
	int n,L=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",ch+L);
		st[i]=L;
		len[i]=strlen(ch+L);
		L+=len[i]+1;
		ch[L-1]='a'-1;
	}
	DC3 dc3=DC3(rank,SA,L,ch);
	dc3.solve();
	dc3.getH(h);
	build_rmq(L);
	for(int i=0;i<n;i++){
		int x=rank[st[i]];
		int fr=0,to=L-1;
		int tmp=x;
		while(tmp-fr>1){
			int mid=(tmp+fr)/2;
			if(query(mid,x)>=len[i])tmp=mid;
			else fr=mid;
		}
		if(query(x,to)>=len[i])to++;
		else {
			tmp=x;
			while(to-tmp>1){
				int mid=(tmp+to)/2;
				if(query(x,mid)>=len[i])tmp=mid;
				else to=mid;
			}
		}
		printf("%d\n",to-fr-1);
	}
}
