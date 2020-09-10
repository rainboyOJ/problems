#define UVa  "LT9-21.1336.cpp"		//Fixing the Great Wall
char fileIn[30] = UVa, fileOut[30] = UVa;
 
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
 
using namespace std;
 
struct Wall {
    int x;
    double c, d;
    bool operator < (const Wall& w2) const {
        return x < w2.x;
    }
};
 
//Global Variables. Reset upon Each Case!
const int maxn = 1000 + 10, LEFT = 0, RIGHT = 1;
const double INF = 1e30;
int n, v, sx;
Wall walls[maxn];
double pref_d[maxn];
double sumc;
double d[maxn][maxn][2];
int vis[maxn][maxn][2];
int kase = 0;
/////
 
double cost(int l, int r, int s, int t) {
    double result = 0.0;
    double sumd = pref_d[n] - (pref_d[r] - pref_d[l] + walls[l].d);
    int dist = abs(walls[s].x - walls[t].x);
    double tm = (double)dist / (double)v;
    result = sumd*tm;
    return result;
}
 
double dp(int l, int r, int k) {
    if(l == 0 && r == n) return 0;
    double& ans = d[l][r][k];
    if(vis[l][r][k] == kase) return ans;
    vis[l][r][k] = kase;
    ans = INF;
 
    double s = (k==LEFT)?l:r;
    if(l > 0)      //go left
        ans = min(ans, dp(l-1, r, LEFT) + cost(l, r, s, l-1));
    if(r < n)      //go right
        ans = min(ans, dp(l, r+1, RIGHT) + cost(l, r, s, r+1));
    return ans;
}
 
int main() {
    memset(vis, 0, sizeof(vis));
    while(scanf("%d%d%d", &n, &v, &sx) == 3 && n) {
        kase ++;
 
        walls[0].x = sx; walls[0].c = walls[0].d = 0;
        int sindex;
        sumc = 0;
        for(int i = 1; i < n+1; i ++) {
            scanf("%d%lf%lf", &walls[i].x, &walls[i].c, &walls[i].d);
            sumc += walls[i].c;
        }
        sort(walls, walls + n + 1);
        for(int i = 0; i < n+1; i ++) {
            if(walls[i].x == sx) sindex = i;
 
            pref_d[i] = walls[i].d;
            if(i) pref_d[i] += pref_d[i-1];
        }
 
        printf("%.0f\n", floor(dp(sindex, sindex, LEFT)+(double)sumc));
 
    }
    return 0;
}
