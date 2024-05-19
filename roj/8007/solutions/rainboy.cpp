
#include <iostream>
#include <cstring>
using namespace std;
char a[10000];

char b[10000];

//b 进制的字符串s转成10进制,
// len 表示s的长度
long long b2dec(char *s,int len,int b){
    long long ans = 0;
    long long base = 1;
    for(int i = len;i>=1;i--) {
        ans += (s[i]-'0') *base;
        base *= b;
    }
    return ans;
}


int main (int argc, char *argv[]) {
    //读取数据与计算字符串的长度
    cin >> a+1;
    // string length
    int la = strlen(a+1);
    cin >> b +1;
    int lb = strlen(b+1);

    /* cout << b2dec(a,la,2) << "\n"; */
    /* cout << b2dec(b,lb,3) ; */
    // 枚举哪个位置错了
    for(int i =1;i<=la;i++){
        for(int j = 1;j<=lb;j++){
            /* cout << i << " " << j << endl; */


            char ta = a[i]; //记录 a[i]原来是哪个数字
            //改变数字 1变0,变1
            if(a[i] == '0') a[i] = '1';
            else a[i] = '0';

            char tb = b[j]; //记录 b[j]原来是哪个数字

            //枚举b[j]应该改成谁
            for(int k = 0;k<3;k++){
                //相同就不改
                if( k == b[j] -'0') continue;
                //改b[j]
                b[j] = k+'0';

                //转成10进制
                long long t1 = b2dec(a,la,2);
                long long t2 = b2dec(b,lb,3);
                // 得到正确的解,输出,然后结束main函数
                if( t1 == t2) {
                    cout << t1 ;
                    return 0;
                }
            }


            //恢复原来的数
            a[i] = ta;
            b[j] = tb;
        }
    }
    return 0;
}

