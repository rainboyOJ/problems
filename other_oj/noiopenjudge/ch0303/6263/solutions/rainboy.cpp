#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int maxn = 1e5;

char str[maxn];
char a[maxn];
int idx;

template<typename T = int,int siz = maxn>
struct mystack{
    T sta[maxn];
    int head = 0;

    void clear() { head = 0;}

    void push(T a) { sta[head++] = a;}

    void pop(){head--;}

    T top() { return sta[head-1];}

    bool empty() { return head == 0;}
};

mystack<char> sta_opt;
mystack<bool> sta_num;

char prio[] = {'(',')','|','&','!','('};
int prio_len = sizeof(prio) /sizeof(prio[0]);

int priority_num(char a) {
    for(int i = 0 ; i< prio_len ;i++)
    {
        if( prio[i] == a)
            return i;
    }
    return -1;
}

//判断 a是否比c 优先级高
bool priority(char a,char c) {
    // 因为这个时候 操作数还没有出现
    // 
    if( a == '!' && c == '!') // 这个比较特别
        return false;
    return priority_num(a) >= priority_num(c);
}

//过滤空格,存到a里
void filter_space() {

    int len = strlen(str);
    idx = 0;
    for(int i = 0 ;i< len;i++)
    {
        if( str[i] == ' ') continue;
        a[++idx] = str[i];
    }
}

//计算数字
void calc() {

    //从sta_opt取一个运算符号
    char c = sta_opt.top();
    sta_opt.pop();
    bool b = sta_num.top();
    sta_num.pop();
    if( c == '|') {
        bool a = sta_num.top();
        sta_num.pop();
        sta_num.push(a || b);
        // cout <<  a << c << b << endl;
    }
    else if( c == '&')
    {
        bool a = sta_num.top();
        sta_num.pop();
        sta_num.push(a && b);
        // cout <<  a << c << b << endl;
    }
    else if( c == '!') {
        sta_num.push(!b);
        // cout <<   c << b << endl;;
    }
 
}

void work() {
    sta_opt.clear();
    sta_num.clear();
    for(int i =1;i<=idx;i++) {
        char c = a[i];
        if( c == 'F' || c == 'V') {
            sta_num.push( c == 'V');
            continue;
        }

        //运行到这里表示是运算符号

        // ( 必须直接入栈
        // 可以认为 ( 是一个有限级很低的运算符号,
        // 但是它不能让栈里的操作符元素弹出
        // 因为( 可以认为不能和其它操作符 ! & | 发生比较
        if( c == '(')
        {
            sta_opt.push('(');
            continue;
        }

        // 没有比栈顶的优先级高
        while( !sta_opt.empty() && priority(sta_opt.top(),c))
        {
            calc();
        }

        sta_opt.push(c);
        if( c == ')') {
            sta_opt.pop();
            sta_opt.pop();
        }

    }

    while( !sta_opt.empty() )
        calc();

}

int main() {
    
    while( cin.getline(str,maxn)) {
        // cout << str << endl;
        filter_space();
        work();
        if( sta_num.top() )
            cout << "V" << endl;
        else
            cout << "F" << endl;
    }

    return 0;
}

