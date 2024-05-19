#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+5;
const int maxe = 1e6+5;

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    //下标访问
    edge& operator[](int i){ return e[i]; }
    //返回head[u]
    int operator()(int u){ return h[u]; }
} e;

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


int n;
int indeq[maxn]; //每个点的入度,入度为0,表示不在环上
bool vis[maxn];
myqueue<int> que; //队列,进行topsort
int ans = 0x7f7f7f7f;

//把那些,不在环上的点标记
void topsort(){
    while (!que.empty()) {
        int u = que.front();
            // cout << u << endl;
        que.pop();
        for(int ed  = e.h[u]; ~ed; ed = e[ed].next)
        {
            int v = e[ed].v;
            if( --indeq[v] == 0) {
                que.push(v);
            }
        }
    }
}
int dfs(int u) {
    vis[u] = 1;
    int cnt = 1;
    // cout << "dfs " << u << endl;
    for(int ed  = e.h[u]; ~ed; ed = e[ed].next)
    {
        int v = e[ed].v;
        if( indeq[v] == 0 || vis[v]) continue;
        cnt += dfs(v);
    }
    return cnt;
}

int main () {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t;
        std::cin >> t;
        e.add(i,t);
        indeq[t]++;
    }

    //入度为0的点加入队列
    // cout << endl;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( indeq[i] == 0)
            que.push(i);
        // cout << indeq[i] << " ";
    }
    // cout << endl;
    topsort();
    //求最小环
    for(int i =1;i<=n;i++) {
        if( indeq[i] == 0 || vis[i]) continue;
        int t = dfs(i);
        if( ans > t)
            ans = t;
    }
    cout << ans << endl;

    return 0;
}
