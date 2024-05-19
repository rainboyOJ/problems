//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-30 09:56:20
//朴素的暴力算法
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];
int pre_sum[maxn];
int f[maxn];
int f_pre[maxn]; //记录每个点的决策点

//区间和
int range_sum(int l,int r) {
    return pre_sum[r] - pre_sum[l-1];
}

//区间最大值
int max_val(int l,int r) {
    int ret = a[l];
    for(int i = l+1;i <= r ;++i ) // i: l->r
    {
        if( ret < a[i])
            ret = a[i];
    }
    return ret;
}

int main () {
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> a[i];
        pre_sum[i] = pre_sum[i-1] + a[i];
    }

    //初始化 f 为-1,就表示没有被计算过
    memset(f,-1,sizeof(f));
    f[0] = 0; //前0个元素的最值为0
    f[1] = a[1];

    //枚举前i个元素
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = i-1;j >= 0;j--) {
            //和超过了M,那么左面也不需要去计算了
            //因为也肯定会超过M
            if( range_sum(j+1,i) > m)
                break;
            int t = f[j] + max_val(j+1,i);
            if( f[i] == -1){
                f_pre[i] = j;
                f[i] = t;
            }
            else if( f[i] > t){
                f_pre[i] = j;
                f[i] = t;
            }
        }
    }
    #ifdef DEBUG
    // for(int i = 1;i <= n ;++i ) // i: 1->n
    // {
    //     cout << i << " " << f[i] << endl;
    // }
    #endif
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cout << i  << " ";
        std::cout << f[i]  << " ";
        std::cout << f_pre[i]  << "\n";
    }

    // std::cout << f[n] << "\n";

    return 0;
}
