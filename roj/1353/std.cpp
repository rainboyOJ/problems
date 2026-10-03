#include <iostream>
#include <string>
using namespace std;

// 表达式括号匹配：输入一行以 @ 结尾的表达式，
// 判断其中的左右圆括号是否匹配，匹配输出 YES，否则输出 NO。
int main()
{
    string s;
    getline(cin, s);

    int top = 0;      // 栈中左括号的个数（只用计数即可，不需要真的开数组）
    bool ok = true;   // 是否仍然可能匹配

    for (size_t i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if (c == '@')           // @ 是表达式结束符，后面不用看了
            break;
        if (c == '(')           // 左括号入栈
            top++;
        else if (c == ')')      // 右括号尝试与栈顶左括号匹配
        {
            if (top > 0)        // 栈非空：消掉一个左括号
                top--;
            else                // 栈已空还来右括号，必然不匹配
            {
                ok = false;
                break;
            }
        }
    }

    if (ok && top == 0)         // 栈为空说明左右括号完全配对
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
