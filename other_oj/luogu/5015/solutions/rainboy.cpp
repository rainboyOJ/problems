/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 05月 30日 星期日 15:18:42 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */


int main(){
    char c;
    int cnt = 0;
    while( 1) {
        cin >> c;
        if( cin.eof() ) break;
        if( c == ' ' || c == '\n' || c == '\r')
            continue;
        cnt++;
    } 
    printf("%d",cnt);
    return 0;
}

