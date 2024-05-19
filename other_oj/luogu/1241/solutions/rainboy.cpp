#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 1e5+5;
typedef int T;
char str[1005];
bool b[1005]; //b[i] 表示这个字符是事匹配
struct mystack{
    T sta[maxn];
    int head = 0;

    void clear() { head = 0;}

    void push(T a) { sta[head++] = a;}

    void pop(){head--;}

    T top() { return sta[head-1];}

    bool empty() { return head == 0;}
};

mystack a; //定义栈



int main() {
    cin >> str;
    int len = strlen(str); //得到字符串的长度

    //不停的读取字符,直到读取到文件的结尾
    for(int i = 0 ;i< len ;i++){
        char t = str[i];
        if( t == ')') {
            if( !a.empty() &&  str[a.top()] == '(')
            {
                b[a.top()] = 1;
                b[i] = 1;
                a.pop();
            }
            continue;
        }
        else if( t == ']')
        {
            if( !a.empty() && str[a.top()] == '[')
            {
                b[a.top()] = 1;
                b[i] = 1;
                a.pop();
            }
            continue;
        }
        a.push(i); // 加入字符所在的位置
    }
    for(int i =0;i<len;i++)
    {
        if( b[i] ) 
            cout << str[i];
        else {
            if( str[i] == '(' || str[i] == ')')
                cout << "()";
            else
                cout << "[]";
        }
            
    }

    return 0;
}
