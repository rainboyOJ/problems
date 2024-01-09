#include <bits/stdc++.h>
using namespace std;
#define F(i, s, t) for (int i = s; i <= t; ++i)
#define fenc cout << "==========\n"
#define log(a) cout << #a " = " << a << endl

int n, m;
string s;

struct node
{
    char a;  // ( ) 元素的类型
    int pos; //0 位置,方便输出找
};

node _stack[10000];
int top = 0;
void push(node a)
{
    _stack[top] = a; // 压栈
    top++; // 栈顶+1
}

void pop()
{
    top--; // 栈顶出栈
}

node get_top()
{
    return _stack[top - 1]; // 得到栈顶元素
}

bool empty()
{
    return top == 0; // 判断站内是否有元素
}

void work()
{
    top = 0;
    string s2; // 
    F(i, 0, s.length() - 1)
    {
        s2 += ' '; // 与s一样大
        char c = s[i]; // 把s内每个元素提出判断
        if (c == '(') // 右括号进栈才能消掉
        {
            push({'(', i});
        }
        else if (c == ')')
        {
            if (empty() == false && get_top().a == '(') // 栈顶必有 或 全没有
            {
                pop(); // 
            }
            else
            {
                push({')', i});
            }
        }
    }

    for (int i = 0; i < top; i++)
    {
        // cout << _stack[i].a << " " << _stack[i].pos << endl;
        if (_stack[i].a == '(')
            s2[_stack[i].pos] = '$';
        else
            s2[_stack[i].pos] = '?';
    }
    cout << s2 << endl;
}

int main()
{

    int ans = 0;
    while (!cin.eof())
    {
        getline(cin, s); // 读完一行
        if( s.length() == 0) break;
        // std::cout << ++ans << "\n";
        cout << s << endl;
        work();
        // if (cin.eof()) //读完就停止循环
        //     break;
    }
    return 0;
}
