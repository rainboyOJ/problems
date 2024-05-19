#include <iostream>
using namespace std;
const int maxn = 1e5+5;

int n,m;

template<typename T = int,int siz = maxn>
struct myqueue{
    T a[maxn];
    //tail 指向最后一个元素后面一个位置
    //head 指向第一个元素
    int head = 0,tail=0; 

    void clear() { head =tail = 0;}

    void push(T n) { a[tail++] = n;}

    void pop(){head++;}

    T front() { return a[head];}
    T back() { return a[tail-1];}

    bool empty() { return head == tail;}

    int size() { return tail-head;}
};

myqueue que; //队列
int bucket[maxn]; //桶
int cnt; //计算次数


int main() {
    std::cin >> n >> m;

    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int t;
        std::cin >> t;
        if(  bucket[t] == 1) continue;

        cnt++;
        bucket[t] = 1;

        if( que.size() >= n){
            bucket[que.front()] =0;
            que.pop();
        }
        // cout << t << endl;

        que.push(t);

    }
    cout << cnt<<endl;

    return 0;
}

