#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
const int maxn = 1e5 + 5;
int n, I, h, r,	x, y, d[maxn];
map<pair<int, int>, bool> mp; 

int main() {
	scanf("%d%d%d%d", &n, &I, &h, &r);
	for (int i = 1; i <= r; i++) {
		scanf("%d%d", &x, &y);
		if (x > y) swap(x, y);	
		//判断是否重复 
		if (mp[make_pair(x, y)]) continue;
		//[x + 1, y - 1]的范围里面的数每个减1
		d[x + 1]--;
		d[y]++;			
		mp[make_pair(x, y)] = 1; 
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = ans + d[i];
		printf("%d\n", ans + h); //最终的答案要加r  因为默认全部都是r为初始 
	}	
	return 0;
}

