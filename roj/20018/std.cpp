#include <bits/stdc++.h>
using namespace std;
long long sum, c, ans;
string s;
int main() {
    cin >> s >> c;
    for (int i = 0; i < s.length(); ) {
        char ch = s[i++]; 
        long long cc = 0;
        //字符是字母的时候 
        //字符串转十进制 
        //9  cc=9
        //7  cc=cc*10+7=97
        //1  cc=cc*10+1=971
        //2  cc=cc*10+2=9712
        while (i < s.length() && isdigit(s[i])) {
            cc = cc * 10 + (s[i] - '0'); 
            i++;
        }
        sum += cc;
    }
//    c=(c-1)%sum+1;
    //sum刚好是c的倍数的时候,sum->0 
    c %= sum;
    for (int i = 0; i < s.length(); ) {
        char ch = s[i++];
        long long cc = 0;
        while (i < s.length() && isdigit(s[i])) {
            cc = cc * 10 + (s[i] - '0'); 
            i++;
        }
        if (ans + cc > c) {
            cout << ch << endl;
            return 0;
        }
        ans += cc;
    }
    return 0;
}
