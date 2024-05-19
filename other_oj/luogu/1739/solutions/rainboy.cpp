#include <iostream>
using namespace std;


const int maxn = 1e5+5;

int sta[maxn];
int  head= 0;
void push(char a){ sta[head++] = a; }
void pop() { head--; }
int top() { return sta[head-1]; }
bool empty() { return head == 0; }


int main(int argc, char const *argv[])
{
    char c;
    for( ;1; ) {
        cin >> c;
        if( c == '@')
            break;
        if( c == '(')
            push(c);
        else if( c == ')')
        {
            if( empty() ) {
                cout << "NO";
                return 0;
            }
            pop();
        }
    }
    if( empty())
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
