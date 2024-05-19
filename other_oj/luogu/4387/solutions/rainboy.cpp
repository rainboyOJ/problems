#include <iostream>
using namespace std;

int T,n;

const int maxn = 1e5+5;
template<int siz = maxn,typename T = int>
struct mystack{
    T sta[maxn];
    int head = 0;

    void clear() { head = 0;}

    void push(T a) { sta[head++] = a;}

    void pop(){head--;}

    T top() { return sta[head-1];}

    bool empty() { return head == 0;}
};

int a[maxn];
int b[maxn];

mystack sa,sb; //定义两个栈

int main() {
    cin >> T;
    while( T-- ) {
        cin >> n;
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            cin >> a[i];
        }
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            cin >> b[i];
        }


        sa.clear();
        sb.clear();
        for(int i = n;i >=1 ;--i ) // i: 1->n
        {
            sb.push(b[i]);
        }

        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            sa.push(a[i]);

            if( sa.empty() || sb.empty()) continue;

            //尽可能的弹出元素
            while( !sa.empty() ) {

                if( sb.empty() ) break;

                //相同就弹出
                if( sa.top() == sb.top() ) {
                    sa.pop();
                    sb.pop();
                }
                else break;
            }
        }


        if( sa.empty())
            cout << "Yes\n";
        else
            cout << "No\n";

    }

    return 0;
}
