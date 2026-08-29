#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    long long base = 0;
    vector<long long> diff; diff.reserve(n);
    for (int i = 0; i < n; ++i) {
        base += b[i];
        long long d = a[i] - b[i];
        if (d > 0) diff.push_back(d);
    }
	//一开始默认所有书都是不带走的 
    if ((int)diff.size() > m) {
        nth_element(diff.begin(), diff.begin() + m, diff.end(), greater<long long>());
        //快速排序
		//只需要知道前m大
		 
		
		diff.resize(m);
    }
    long long extra = 0;
    for (auto v : diff) extra += v;

    cout << (base + extra) << '\n';
    return 0;
}
