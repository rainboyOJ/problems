#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1e5+5;

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

typedef  long long ll;
myqueue<ll> a;
myqueue<ll> b;
int s,n;


int main() {
    while (cin >> s >> n) {
        //特别的处理第一个元素.
        int cnt = 1;
        a.clear();
        b.clear();
        ll t = s;
        if( cnt >= n) {
            cout << t <<endl;
            continue;
        }
        a.push(2*t+1);
        b.push(3*t+1);
        int pre = t;
        while(1) {
            ll t1 = 0x7f7f7f7f7f7f7f7f;
            ll t2 = 0x7f7f7f7f7f7f7f7f;

            if( !a.empty()) t1=a.front();
            if( !b.empty()) t2=b.front();

            if( t1 <= t2) {
                t = t1;
                a.pop();
            }
            else
            {
                t= t2;
                b.pop();
            }
            //如果和上一个取的数一样大,
            // 根据集合中元素不能一样,所以这个不能计算
            if( t == pre) continue;
            cnt++;
            pre = t;
            // cout << cnt << " " << t<< "\n";
            if( cnt == n) {
                cout << t << endl;
                break;
            }
            if(a.empty() ||2*t+1 != a.back() )
                a.push(2*t+1);
            if(b.empty() ||3*t+1 != b.back() )
                b.push(3*t+1);
        }
    }
    int m = a.tail;
    if( m < b.tail)
        m = b.tail;
        
    // for(int i =0;i<m;i++)
    // {
    //     cout << a.a[i] << " " << b.a[i] << endl;
    // }

    return 0;
}
