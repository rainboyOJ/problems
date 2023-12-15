#include <bits/stdc++.h> 
using namespace std;
#define ll long long
const int maxn = 2e3 + 5;
ll dp[maxn][maxn][2], a[maxn];
// 0 not vall point 1 is vall point
int main(){
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	ll ans = 0;
	for(int i = 2; i < n; i++){
		for(int j = 0; j <= k; j++){
			if(a[i] < a[i-1] && a[i] < a[i+1]){ //第i个点原来就是山谷点
				dp[i][j][1] = dp[i-1][j][0] + a[i];
				dp[i][j][0] = dp[i-1][j][1];
			}else if(a[i] < a[i-1]){
				if(j != 0)
					dp[i][j][1] = dp[i-1][j-1][0] + min(a[i-1]-1, a[i+1]-1);
				dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1]);
			}else{
				if(j != 0)
				dp[i][j][1] = dp[i-1][j-1][0] + min(a[i-1]-1, a[i+1]-1);
				dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1]);
			}
//			cout << i << " " << j << " " << dp[i][j][0] << " " << dp[i][j][1] << endl;
			ans = max(ans, dp[i][j][0]);
			ans = max(ans, dp[i][j][1]);
		}
	}
	cout << ans << endl;
} 
