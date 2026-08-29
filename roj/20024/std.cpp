#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll NEG_INF = -(1LL << 60);

inline int bit(int x, int k) { return (x >> k) & 1; }

/* 状态编码：
   | colB_colored(3bit) | colB_pattern(3bit) | colA_colored(3bit) | colA_pattern(3bit) |
   最右边的是最旧那列（滑窗左端) */
inline int encode(int pa, int ca, int pb, int cb) {
    return pa | (ca << 3) | (pb << 6) | (cb << 9);
}
inline void decode(int s, int &pa, int &ca, int &pb, int &cb) {
    pa = s & 7;
    ca = (s >> 3) & 7;
    pb = (s >> 6) & 7;
    cb = (s >> 9) & 7;
}

int main() {
    // freopen(".out","w",stdout);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> w(3, vector<int>(n));   // w[row][col]
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < n; ++c)
            cin >> w[r][c];

    /* n = 1 或 2：只有纵向三连线 */
    if (n <= 2) {
        ll best = NEG_INF;
        for (int p0 = 0; p0 < 8; ++p0) {
            for (int p1 = 0; p1 < (n == 2 ? 8 : 1); ++p1) {
                ll cur = 0;
                /* 列 0 */
                if (p0 == 0 || p0 == 7) {
                    int sgn = (p0 & 1) ? 1 : -1;
                    for (int r = 0; r < 3; ++r) cur += 1LL * w[r][0] * sgn;
                }
                if (n == 2 && (p1 == 0 || p1 == 7)) {
                    int sgn = (p1 & 1) ? 1 : -1;
                    for (int r = 0; r < 3; ++r) cur += 1LL * w[r][1] * sgn;
                }
                best = max(best, cur);
            }
        }
        cout << best << '\n';
        return 0;
    }

    /* n >= 3：DP */
    const int SZ = 4096;
    vector<ll> dp(SZ, NEG_INF), ndp(SZ, NEG_INF);

    /* 枚举前两列初始状态 */
    for (int p0 = 0; p0 < 8; ++p0)
        for (int p1 = 0; p1 < 8; ++p1) {
            int s = encode(p0, 0, p1, 0);
            dp[s] = 0;
        }

    /* 主循环：处理列 idx = j (0-based), j 从 2 到 n-1 */
    for (int j = 2; j < n; ++j) {
        int idxFinal = j - 2;                       // 本轮要定型的列
        fill(ndp.begin(), ndp.end(), NEG_INF);

        for (int st = 0; st < SZ; ++st) if (dp[st] > NEG_INF) {
            int pa, ca, pb, cb;
            decode(st, pa, ca, pb, cb);
            
            // printf("%d:%d,%d,%d,%d\n",j,pa,ca,pb,cb);

            for (int pc = 0; pc < 8; ++pc) {        // 新列摆放
                int ca2 = ca, cb2 = cb, cc = 0;
                ll gain = 0;

                auto add_cell = [&](int row, int sym, int &cflag, const int *wcol, bool score_now) {
                    if (!(cflag & (1 << row))) {
                        if (score_now)
                            gain += 1LL * wcol[row] * (sym ? +1 : -1);
                        cflag |= (1 << row);
                    }
                };

                const int wA[] = {w[0][idxFinal], w[1][idxFinal], w[2][idxFinal]};    // 权值列指针

                for (int r = 0; r < 3; ++r) if(bit(ca, r)) gain += wA[r] * (bit(pa, r) ? +1 : -1);

                /* 1. 纵向三连线（整列相同） */
                if (pa == 0 || pa == 7) {
                    int sym = pa & 1;
                    for (int r = 0; r < 3; ++r)
                        add_cell(r, sym, ca2, wA, true);
                }

                /* 2. 横向三连线（三行各自判断） */
                for (int r = 0; r < 3; ++r) {
                    int s1 = bit(pa, r), s2 = bit(pb, r), s3 = bit(pc, r);
                    if (s1 == s2 && s2 == s3) {
                        add_cell(r, s1, ca2, wA, true);   // (r, colA)
                        add_cell(r, s1, cb2, wA, false);  // (r, colB)   (重量以后结算)
                        cc |= (1 << r);                   // (r, colC)
                    }
                }

                /* 3. 对角线 ↘ (0,1,2) */
                if (bit(pa, 0) == bit(pb, 1) && bit(pb, 1) == bit(pc, 2)) {
                    int sym = bit(pa, 0);
                    add_cell(0, sym, ca2, wA, true);   // (0, colA)
                    add_cell(1, sym, cb2, wA, false);  // (1, colB)
                    cc |= (1 << 2);                    // (2, colC)
                }

                /* 4. 对角线 ↗ (2,1,0) */
                if (bit(pa, 2) == bit(pb, 1) && bit(pb, 1) == bit(pc, 0)) {
                    int sym = bit(pa, 2);
                    add_cell(2, sym, ca2, wA, true);   // (2, colA)
                    add_cell(1, sym, cb2, wA, false);  // (1, colB)
                    cc |= (1 << 0);                    // (0, colC)
                }

                int st2 = encode(pb, cb2, pc, cc);
                ndp[st2] = max(ndp[st2], dp[st] + gain);
                // printf("(%d,%d,%d,%d):%lld\n",pb,cb2,pc,cc,ndp[st2]);
            }
        }
        dp.swap(ndp);
    }

    /* 收尾：还剩列 n-2 与 n-1，只可能出现“纵向”三连线 */
    ll ans = NEG_INF;
    for (int st = 0; st < SZ; ++st) if (dp[st] > NEG_INF) {
        int pa, ca, pb, cb;
        decode(st, pa, ca, pb, cb);
        ll val = dp[st];

        /* 列 n-2 */
        for (int r = 0; r < 3; ++r) if(bit(ca,r)) val += 1LL * w[r][n - 2] * (bit(pa,r) ? +1 : -1);
        if (pa == 0 || pa == 7) {
            int sym = pa & 1;
            for (int r = 0; r < 3; ++r)
                if (!(ca & (1 << r)))
                    val += 1LL * w[r][n - 2] * (sym ? +1 : -1);
        }
        /* 列 n-1 */
        for (int r = 0; r < 3; ++r) if(bit(cb,r)) val += 1LL * w[r][n - 1] * (bit(pb,r) ? +1 : -1);
        if (pb == 0 || pb == 7) {
            int sym = pb & 1;
            for (int r = 0; r < 3; ++r)
                if (!(cb & (1 << r)))
                    val += 1LL * w[r][n - 1] * (sym ? +1 : -1);
        }
        // if(val > 100) printf("(%d,%d,%d,%d) %lld %lld\n",pa,ca,pb,cb,dp[st],val);
        ans = max(ans, val);
    }

    cout << ans << '\n';
    return 0;
}
/*
4
1 2 3 4
4 -100 2 1
1 3 1 3
------------
119
*/