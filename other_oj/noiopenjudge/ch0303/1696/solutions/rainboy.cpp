#include <iostream>
#include <cmath>
using namespace std;

char str[1000][100];
int cnt;

const int maxn = 1e5+5;
template<typename T = int,int siz = maxn>
struct mystack{
    T sta[maxn];
    int head = 0;

    void clear() { head = 0;}

    void push(T a) { sta[head++] = a;}

    void pop(){head--;}

    T top() { return sta[head-1];}

    bool empty() { return head == 0;}

    int size() { return head; }
};

mystack sta;






int main() {

    while( cin >> str[cnt]) {
        cnt++;
    }
    int new_idx = cnt;
    for(int i = 0;i < cnt ;i++) {

        if(str[i][0] >= '0' && str[i][0] <='9') {

        }

    }
    // cout << num_sta.top();
    printf("%f\n",num_sta.top());

    return 0;
}
