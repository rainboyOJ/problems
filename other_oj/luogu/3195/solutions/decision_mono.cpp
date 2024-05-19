// 使用 决策单调性 , 实现的
//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-19 14:49:04

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
typedef  long long ll;
int n,L;
int a[maxn];
//前缀和
ll pre_sum[maxn];
ll f[maxn];

//存入栈中的点
struct node {
    int p;  //最优决策点
    int l,r; // [l,r]的决策点都是p
};

// 求[j+1,i]放在一起的值
ll val(int j,int i) {
    ll len = i-(j+1)+pre_sum[i] - pre_sum[j];
    len -=L;
    return len * len;
}

void init() {
    std::cin >> n >> L;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        pre_sum[i] = pre_sum[i-1];
        pre_sum[i] += a[i];
    }
}


//栈模板
template<typename T = int,int siz = maxn>
struct mystack{
    T sta[siz+5];
    int head = 0;

    void clear() { head = 0;}

    void push(T a) { sta[head++] = a;}

    void pop(){head--;}

    T top() { return sta[head-1];}

    bool empty() { return head == 0;}

    int size() { return head;}
};

mystack<node> sta;

//二分的代码

int mid(int l,int r) {
    return (l+r) >> 1; //这是最快的写法
}

//bs_find = binary search find
template <typename F>
int bs_find(int l,int r,F check) {
    while( l < r) {
        int m = mid(l,r);
        if( check(m)) //成立
            r = m;
        else //不成立,抛弃左半边
            l = m+1;
    }
    return l ;
}

//输出栈内的内容
void debug_sta() {
    cout << "p[i]: \n";
    // for(int i = 0 ;i< sta.size();i++) {
    //     node t = sta.sta[i];
    //     for(int j = t.l; j<=t.r ;j++)
    //         cout << t.p << " ";
    // }
    for(int i = 0 ;i< sta.size();i++) {
        cout << "p: " << sta.sta[i].p << " ";
        cout << "l: " << sta.sta[i].l << " ";
        cout << "r: " << sta.sta[i].r << "\n";
    }
    cout << endl;
}

void debug_f() {
    cout << "f[i]: ";
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << f[i] << " ";
    }
    cout << endl;
}



int main (int argc, char *argv[]) {
    init();
    f[0] = 0;
    sta.push({0,1,n});
    for(int i = 1;i <= n ;++i ) // 前i个元素
    {
#ifdef DEBUG
        cout << "before calc i= " << i << endl;
        debug_f();
        debug_sta();
        cout << endl;
#endif

        f[i] = 0x7f7f7f7f7f7f7f7f;
        // 先找到i的决策点p,然后计算出f[i]的值
        //找到包含i的区间
        int pos = bs_find(0,sta.size(),[i](int m){
            //判断这个m所在的区间在i的的左边
            //判断方法: 当前node的r大于等于i,
            return sta.sta[m].r >= i;
            
        });
        pos = sta.sta[pos].p; // 决策点
        f[i] = f[pos] + val(pos,i);


        // 单调栈
        // 从后面向前找,如果点i比当前节点的p(决策点)优秀,就出栈

        while( !sta.empty()) {
            node t = sta.top();

            //是否更优秀
            ll org = f[t.p] + val(t.p,t.l);
            ll now = f[i] +val(i,t.l);
            if( now <= org) { //更加优秀
                sta.pop();
            }
            else { //不是更优秀
                //在区间 [t.l,t.r+1] 找到开头的那个点
                sta.pop();
                int pos = bs_find(t.l,t.r+1,[p=t.p,i](int m){
                    ll org = f[p] + val(p,m);
                    ll now = f[i] +val(i,m);
                    return now <= org;
                });
                if( pos > n){ // 
                    sta.push(t);
                }
                else {
                    sta.push({t.p,t.l,pos-1});
                    sta.push({i,pos,n});
                }
                break;
            }
        }

#ifdef DEBUG
        cout << "after calc i= " << i << endl;
        debug_f();
        debug_sta();
        cout << endl;
#endif
    }
    cout << f[n] << endl;


    return 0;
}
