#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

char char2num[1000];
int n;
char num[1000];
int ans[1000];


//转成10进制,原来是a进制
// len num数组里存的数字的长度
ll todec(ll a,int len){
    ll ans = 0;
    ll base = 1;
    for(int i = len ;i>=1;i-- ) {
        int t = char2num[ num[i] ]; //得到a[i]对应的数字是多少
        ans += t * base;
        base *=a;
    }
    return ans;
}

//10进制转成对应b进制,然后输出
void decto(ll dec,ll b){
    int cnt = 0;

    while(dec) {
        ans[++cnt] = dec % b;
        dec /= b;
    }

    for(int i = cnt ;i>=1;i--) {
        if( ans[i] < 10)
            cout << ans[i] ;
        else
        {
            //转成对应的字符类型
            char t =ans[i] - 10 +'A';
            //输出字符
            cout << t;
        }
    }
    cout <<endl;
}





int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i ='0' ;i <='9';i++)
    {
        char2num[i] = i - '0';
    }
    for(int i ='A' ;i <='Z';i++)
    {
        char2num[i] = i - 'A'+10;
    }


    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> num+1;
        int len = strlen(num+1); //求字符串的长度
        int a,b; //a,b进制
        cin >> a >> b;
        ll dec  = todec(a,len);
        decto(dec,b);
    }
    return 0;
}

