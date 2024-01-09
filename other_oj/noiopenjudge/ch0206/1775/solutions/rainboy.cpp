#include<bits/stdc++.h>
using namespace std;
int T,M,t[102],v[102],f[102][1002]={0};
int main(){
	int i,j;
	cin>>T>>M;
	for(int i=1;i<=M;i++){
		cin>>t[i]>>v[i];
	}
	for(i=1;i<=M;i++){
		for(j=1;j<=T;j++){
			if(j<t[i]) 
			    f[i][j] = f[i-1][j];
			else
			    f[i][j]=max(f[i-1][j],f[i-1][j-t[i]]+v[i]);
		}
	}
	cout<<f[M][T]<<endl;
	return 0;
}
