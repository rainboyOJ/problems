#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];

    const int MAXCODE = 19683; // 3^9
    vector<char> seen(MAXCODE, 0);

    auto mapColor = [](char c) -> int {
        if (c == 'R') return 0;
        if (c == 'G') return 1;
        return 2; // 'B'
    };

    int H = n / 3, W = m / 3;
    int distinct = 0;
    for (int bi = 0; bi < H; ++bi) {
        for (int bj = 0; bj < W; ++bj) {
            int code = 0;
            int baseRow = bi * 3;
            int baseCol = bj * 3;
            for (int di = 0; di < 3; ++di) {
                for (int dj = 0; dj < 3; ++dj) {
                    code = code * 3 + mapColor(g[baseRow + di][baseCol + dj]);
                }
            }
            if (!seen[code]) {
                seen[code] = 1;
                ++distinct;
            }
        }
    }
    cout << distinct << '\n';
    return 0;
}
