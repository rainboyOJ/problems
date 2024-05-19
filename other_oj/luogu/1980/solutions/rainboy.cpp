#include <bits/stdc++.h>
using namespace std;

int main(){
	int n,m;
    std::cin >> n >> m;
	int i,ans=0;
	for(i=1;i<=n;i++){ //把数字进行拆分
		int x = i;
		while( x !=0 ){
			int g = x % 10;
			if( g == m)
				ans++;
			x = x / 10;
		}
	}
    std::cout << ans << "\n";


	return 0;
}
