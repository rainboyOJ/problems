/* author: Rainboy  email: rainboylvx@qq.com  time: 2020年 08月 04日 星期二 09:52:38 CST */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;
int n,m;
char s[1005];


int main(){
    cin >> s;
    int end = 0;
    if( s[0] == '-'){
        cout << '-';
        end = 1;
    }
    int len = strlen(s);
    int i;
    bool flag = 0; //0表示 没有非0元素输出
    //倒过来
    for( i =len-1;i>=end;i--){
        if( s[i] == '0' && flag == 0 )
            continue;
        else {
            flag = 1;
            cout << s[i];
        }
    }

    //特殊情况,只有一个0
    if(flag == 0)
    {
        cout << "0"<<endl;
    }
    return 0;
}

