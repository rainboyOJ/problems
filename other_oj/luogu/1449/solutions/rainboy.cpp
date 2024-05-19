#include <iostream>
#include <cstring> //使用 strlen
using namespace std;

const int maxn = 1e5+5;

char str[100005];
int len; //字符串的长度

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

mystack sta; //定义栈
int num  = 0;
int ans; //最终的答案


int main() {

    cin >> str ;//读取字符串
    len = strlen(str);

    for(int i =0 ;i< len ;i++) {
        char c = str[i];

        if( c == '@') break;
        if( c >= '0' && c <= '9')
        {
            num= num *10 + (c - '0');
            continue;
        }

        if( c == '.' ) {
            sta.push(num);
            num = 0;
            continue;
        }

        //是运算符号,取两个数
        int b = sta.top();
        sta.pop();
        int a = sta.top();
        sta.pop();
        // cout << a << c << b << endl;

        if( c == '/')
        {
            sta.push(a /b);
        }
        else if( c == '+') {
            sta.push(a +b);
        }
        else if( c == '-') {
            sta.push(a -b);
        }
        else if( c == '*') {
            sta.push(a *b);
        }
    }

    cout << sta.top();

    return 0;
}
