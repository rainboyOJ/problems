#include <iostream>
using namespace std;
//全局变量
int n;
char j;
int ans;
int main() {
    cin >> n >> j; //读取数据
    if( n <=1000 ){ //重量在1000克以内(包括1000克),
        ans = 8;
    }
    else {
        n -= 1000; //去除1000克的部分
        ans = 8; // 原始的8元
        ans += n / 500 * 4; // 生每500克4元,
        if( n % 500 !=0 ) // 有不足500的部分
            ans += 4;
    }

    if( j == 'y')
        ans += 5;

    cout << ans;
    return 0;
}
