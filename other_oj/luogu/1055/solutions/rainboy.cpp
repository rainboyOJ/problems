//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-06 22:10:21
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
char a[maxn];
int cnt = 0;
int tot = 0; //数字的和
int last_num;

int main (int argc, char *argv[]) {
    cin >> a+1; //读取这个字符串
    int len = strlen(a+1); //求出字符串的长度
    for(int i = 1;i <= len ;++i ) // i: 1->len
    {
        if( a[i] == '-') continue;
        int t = a[i] - '0'; //转成数字
        cnt++; // 这是第几个数字
        if( cnt > 9) break; // 超过了9个 就结
        tot = tot + cnt * t;
    }
    int mod = tot % 11;

    //第13个位置一定是最后一个元素
    if( a[13] == 'X')
        last_num = 10;
    else
        last_num = a[13] - '0';

    if( last_num == mod) {
        cout << "Right";
    }
    else {
        a[13] = '\0'; //把最后一个元素变成字符串结尾符号
        // 这样最后一个元素就不会输出了
        cout << a+1;
        if( mod == 10)
            cout << "X";
        else
            cout << mod;
    }


    return 0;
}
