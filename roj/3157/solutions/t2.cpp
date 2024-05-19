#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int n,m; // 
struct node {
    // l表示粉刷的长度
    // s 需要包含的木板
    // p price,报酬
    int l,p,s;
};
node a[maxn];

// 前i个工匠,在j个木板下的最大报酬
// = 0 表示不可能
int f[105][16005]; 

//这个区间[s,e]下,在报酬p下的工资
int val(int s,int e,int p) {
    return (e-s+1) * p;
}

int main() {
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        cin >> a[i].l;
        cin >> a[i].p;
        cin >> a[i].s;
    }
    std::sort(a+1,a+1+m,[](node &a,node &b){
        return a.s < b.s;
    });

    for(int i =1;i<=m;i++) { //枚举工匠
        // int right = a[i].s + a[i].l -1; //终止位置
        for(int j = 1 ;j <= a[i].s - 1 ;j ++)
            f[i][j] = max(f[i-1][j],f[i][j-1]);
        int end = min(a[i].s + a[i].l - 1,n);


        //枚举j这个位置,也就是工匠粉刷的终点
        for(int j = a[i].s ;j<=end;j++) {
            f[i][j] = max(f[i-1][j],f[i][j-1]);
            // 在这个j终点的位置条件下,k应该从哪里开始
            int start = max(j - a[i].l+1,1); //至少是1

            //枚举k这个位置,也就是工匠的粉刷的起点
            for(int k  = start ;k<= a[i].s;k++) {
                f[i][j] = max(f[i][j],f[i-1][k-1] + val(k,j,a[i].p));
            }
            // == 调试用
            // cout << "f[";
            // cout << i  << "][";
            // cout << j << "]=";
            // cout << f[i][j] << endl;
        }
        for(int j = end+1 ;j <= n ;j ++)
            f[i][j] = max(f[i-1][j],f[i][j-1]);
    }
    cout << f[m][n] << endl;

    // for(int i = 1;i <= m ;++i ) // i: 1->m
    // {
    //     for(int j = 1;j <= n ;++j ) // j: 1->n
    //     {
    //         cout << f[i][j] << " ";
    //     }
    //     std::cout  << "\n";
    // }

    return 0;
}

