#include <bits/stdc++.h>
using namespace std;
const int maxn = 25*2500 + 5;

char a[maxn];
int w = 0;
int l = 0;
int len;

int _abs(int a,int b) {
    int c = a -b;
    if( c < 0)
        return -c;
    return c;
}

int _max(int a,int b) {
    if( a < b) 
        return b;
    return a;
}

//cnt 表示分制
void work(int cnt) {
    w = l = 0;
    for (int i = 1; i <= len; i++)
    {
        char c = a[i];
        if( c == 'W') 
            w++;
        else
            l++;
        if( _max(w,l) >= cnt  && _abs(w,l) >=2 ) {
            cout << w << ":" <<l << endl;
            w = 0;
            l = 0;
        }
    }
    cout << w << ":" << l << endl;
}

int main(){
    // 写一点代码,就执行一下,看对不对
    for(int i =1;  1 ;i++){
        char c;
        cin >> c;
        if( c == 'E') break;
        a[i] = c;
    }
    len = strlen(a+1);

    work(11);
    cout << endl;
    work(21);

    return 0;
}
