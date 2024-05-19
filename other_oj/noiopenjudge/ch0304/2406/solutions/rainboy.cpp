#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e5+5;

int n,k,p;

template<typename T = int,int siz = maxn>
struct myqueue{
    T a[siz+5];
    //tail 指向最后一个元素后面一个位置
    //head 指向第一个元素
    int head = 0,tail=0; 

    void clear() { head =tail = 0;}

    void push(T b) { 
        a[tail]= b;
        tail++;
        if( tail > siz)
            tail = 0;
    }

    void pop(){
        head++;
        if(head > siz) head = 0;
    }

    T front() { return a[head];}

    bool empty() { return head == tail;}

    int size() { return tail-head;}
};

myqueue deal; //发牌队列
myqueue bessi; //bessi得到的牌


int main() {
    std::cin >> n >> k >> p;
    for(int i = 1;i <= k ;++i ) // i: 1->k
    {
        deal.push(i);
    }

    // 发k/n轮牌,每一轮,n个人各得到一张牌
    for(int i = 1;i <= k/n ;++i ) // i: 1->k
    {
        for(int j = 1;j<=n;j++) {

            int t = deal.front();
            deal.pop();
            for(int x = 1;x<=p;x++) {
                int t = deal.front();
                deal.pop();
                deal.push(t);
            }
            //bessi得到的牌
            if( j == n) {
                bessi.push(t);
            }
        }
    }

    sort(bessi.a,bessi.a+bessi.size());

    while (bessi.empty() == false) {
        cout << bessi.front() << "\n";
        bessi.pop();
    }

    return 0;
}
