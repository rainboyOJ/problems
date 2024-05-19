//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-18 17:43:27
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int c; // color cnt
int cost;
int color[maxn];
int price[maxn];

int min_bucket[1005][1005];

void init_min_bucket() {
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        min_bucket[i][i] = price[i];
    }
    //枚举区间的起点
    for(int i = 1;i<=n;i++) {
        //枚举区间的终点
        for(int j = i+1;j<=n;j++) {
            min_bucket[i][j] =min(min_bucket[i][j-1],price[j]);
        }
    }
}

int min_range(int l,int r) {
    return min_bucket[l][r];
}

//以i个客栈为结尾有多少个
int find(int I) {
    int sum = 0;
    for(int i =1;i< I;i++) {
        if( color[i] != color[I]) continue;
        if( min_range(i,I) < cost)
            sum++;
    }
    return sum;
}

int main (int argc, char *argv[]) {
    std::cin >> n >> c >> cost;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> color[i] >> price[i];
    }
    init_min_bucket(); // n^2

    //以第i个客栈为结尾
    int ans = 0;
    for(int i = 2;i <= n ;++i ) // n^2
    {
        ans += find(i);
    }
    std::cout << ans << "\n";

    return 0;
}
