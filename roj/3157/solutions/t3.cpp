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


int val2(int i ,int k) {
    return f[i-1][k-1] - a[i].p * k;
}

template<typename T = int,int siz = maxn>
struct myqueue{
    T a[siz+5];
    //tail 指向最后一个元素后面一个位置
    //head 指向第一个元素
    int head = 0,tail=0; 

    void clear() { head =tail = 0;}

    void push(T b) { a[tail++] = b;}

    void pop(){head++;}
    void pop_back(){tail--;}

    T front() { return a[head];}
    T back() { return a[tail-1];}

    bool empty() { return head == tail;}

    int size() { return tail-head;}
};

myqueue<int> que; //创建一个队列



int ans = 0;
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

        // 清空一个队列
        que.clear();

        //处理起始的k区间
        int k_start = max(a[i].s - a[i].l +1,1);
        int k_end = a[i].s;
        //维护一个单调减少的队列
        //初始化这个队列
        for(int k = k_start ; k<= k_end ;k++) {
            int v = val2(i,k);

            //清除后面的没有v好的值
            while( !que.empty() &&  val2(i,que.back()) <= v)
                que.pop_back();
            que.push(k);
        }


        //枚举j这个位置,也就是工匠粉刷的终点
        for(int j = a[i].s ;j<=end;j++) {

            int start = max(j - a[i].l+1,1); //至少是1

            //删除 队头超时的数据
            while( que.front() < start)
                que.pop();


            f[i][j] = max(f[i-1][j],f[i][j-1]);
            // 在这个j终点的位置条件下,k应该从哪里开始

            int Prefix = a[i].p * j + a[i].p; //一定要加的前缀
            //取队头,最值
            int k = que.front();
            f[i][j] = max(f[i][j],Prefix + val2(i,k));

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

