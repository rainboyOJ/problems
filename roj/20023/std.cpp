#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    const int MAX_V = 50;
    vector<vector<int>> cnt(MAX_V + 1, vector<int>(n + 1, 0));
    for (int v = 1; v <= MAX_V; ++v) {
        for (int i = 1; i <= n; ++i) {
            cnt[v][i] = cnt[v][i - 1] + (a[i] == v);
        }
    }

    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;

        int total = 0, mn = 0;
        for (int v = 1; v <= MAX_V; ++v) if(cnt[v][r] > cnt[v][l-1]){
            mn = v;
            break;
        }
        for (int v = mn; v <= MAX_V; ++v) {
            int cur = cnt[v][r] - cnt[v][l - 1];
            if (cur == 0) break; 
            total += cur;
        }
        cout << total << '\n';
    }
    return 0;
}
