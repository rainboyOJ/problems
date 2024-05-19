/* author: Rainboy email: rainboylvx@qq.com  time: 2023年 06月 06日 星期二 21:20:13 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,L;
/* 定义全局变量 */

using db = long double;


//前缀和
long long sum[maxn];
ll dp[maxn];




//斜率优化
struct slope_optimize {


    ll k(int i) { return -2 * B(i);}
    ll B(int i) {return sum[i] +i -L -1;}

    // A(j) 就是xj
    ll A(int j) {return sum[j] +j;}


    //dj 就是 yj
    ll d(int j) {return dp[j] + A(j)*A(j);}

    //两个点的斜率
    double slope(int i,int j) {
        return (d(j) - d(i)) *1.0 / ( A(j) - A(i));
    }

    ll calc_dp(int i,int j) {
        return k(i)*A(j) +d(j)+B(i)*B(i);
    }

} slope_opt;

//队列
struct myque {
    int q[maxn];
    int head,tail;

    int size() const {
        return tail - head;
    }

    bool empty() const {
        return size() == 0;
    }

    void push(int a) {
        q[tail++] = a;
    }

    void del(int i) {
        while( size() > 1 && slope_opt.slope(q[tail-2],i) < slope_opt.slope(q[tail-2], q[tail-1]))
            tail--;
    }
    
    //单调队列不停的删除头部
    void update(double v) {
        while( size() > 1 && slope_opt.slope(q[head],q[head+1]) < v)
            ++head;
    }

    int front() const {
        return q[head];
    }
    int back() const {
        return q[tail-1];
    }


} que;

void init() {
    cin >> n >> L;
    for(int i=1;i<=n;++i){
        cin >> sum[i];
        sum[i] += sum[i-1];
    }
}




int main(int argc,char * argv[]){
    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init(); //读取数据
    que.push(0);
    //尝试每一个点
    for(int i=1;i<=n;i++) {
        que.update(- slope_opt.k(i) );
        dp[i] = slope_opt.calc_dp(i, que.front());

        que.del(i);
        que.push(i);

    }
    cout << dp[n];

    return 0;
}

