#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;
char calculate(char x, char y,char oper )// 计算 x oper y
{
    bool a=(x=='V'),b=(y=='V'),ans;
    if(oper=='|') ans=(a||b);
    else if(oper=='&') ans=(a&&b);
    return ans?'V':'F';
}
char reverse(char x) //将逻辑值取反。其实就是‘！’运算符
{
    if(x=='V')return 'F';
    return 'V';
}
int main()
{
    string in;
    int i,j,len;

    while(getline(cin,in))
    {
        stack<char> Oper,num; //oper保存运算符，num保存运算结果
        queue<char> s;        //s就是前缀表达式
        len=in.length();
        i=len;
        in=" "+in;
        while(i>0)// 从右往左，中缀表达式转前缀表达式
        {
            if(in[i]==' ')
            {
                i--;continue;
            }
            else if(isalpha(in[i])) s.push(in[i--]);//isalpha()函数：如果参数是字母字符，函数返回非零值，否则返回零值
            else if(in[i]=='!')  s.push(in[i--]);    //最高级的运算，直接进入表达式(这里主要是因为！运算符是单目运算符)
            else
            {
                if(in[i]=='&'||in[i]=='|'||in[i]==')')  //低级运算，进栈
                    Oper.push(in[i--]);
                else if(in[i]=='(')  //一个括号结束，弹出中间的所有运算符
                {
                    while(Oper.top()!=')')
                    {
                        s.push(Oper.top());
                        Oper.pop();
                    }
                    Oper.pop();
                    i--;
                }
            }
        }
        while(!Oper.empty())  //栈中剩下的运算符
            s.push(Oper.top()),Oper.pop();

        while(!s.empty())  //计算前缀表达式
        {
            char ch=s.front(); s.pop();
            if(isalpha(ch))  num.push(ch);
            else Oper.push(ch);
            if(!num.empty()&&!Oper.empty()&&Oper.top()=='!')  //单目运算符‘！’；
            {
                char x=num.top();
                num.pop();Oper.pop();
                num.push(reverse(x));
            }
            else if(num.size()>=2&&!Oper.empty())  //双目运算符
            {
                char oper=Oper.top(),x,y;
                Oper.pop();
                x=num.top();num.pop();
                y=num.top();num.pop();
                num.push(calculate(x,y,oper));
            }
        }
        cout<<num.top()<<endl;
    }
}
