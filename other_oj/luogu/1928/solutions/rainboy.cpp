#include <iostream>
#include <string>
#include <cstring>
using namespace std;
const int maxn = 1e6+5;

int n;
int len;

char a[maxn];
char tmp[maxn];
int idx;
int pos;

string read_char() {
    string s ;
    while( a[pos] >= 'A' && a[pos] <='Z')
    {
        s += a[pos];
        pos++;
    }
    return s;
}

int read_num() {
    int num = 0;
    while( a[pos] >= '0' && a[pos] <='9')
    {
        num = num*10 + a[pos] - '0';
        pos++;
    }
    return num;
}

string dfs() {
    char c = a[pos]; //当前位置的值
    if( c == ']') {
        return "";
    }
    int num =1;
    if( c == '[') {
        pos++;
        //读取数字
        num = read_num();
        string s = read_char();
        string ret;
        while( a[pos] != ']')
        {
            s += dfs();
            // 再读取字符串
            string t = read_char();
            s+=t;
        }

        if( a[pos] == ']') //去除这一层对应的]
            pos++;
        for(int i =1;i<=num;i++)
            ret += s;
        return ret;
    }
    return "";
}

int main () {
    cin >> a+1;
    len = strlen(a+1);
    for(pos =1; pos<= len;pos++) {
        char c = a[pos];
        if( c == '[') {
            cout << dfs();
            pos--; // pos 会读取完毕 []所有的内容
        }
        else if( c == ']')
            continue;
        else cout << c;

    }
    cout << endl;
    return 0;
}
