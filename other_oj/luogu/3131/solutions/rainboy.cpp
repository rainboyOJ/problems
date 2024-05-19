#include <iostream>
using namespace std;
const int maxn = 1e5+5;
int n;
int bucket[10];
int s[maxn];
int ans;

int main () {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> s[i];
        s[i] += s[i-1];
        s[i] %= 7; //前缀和的余数
        
        //特殊判断
        // 想一想数据  3 / 1 6 2
        if(s[i] == 0) {
            if ( ans < i) ans = i;
        }

        if( bucket[ s[i] ] != 0)
        {
            if( ans < i - bucket[s[i]]) // 为什么是i - bucket[s[i]] ?
            {
                ans = i - bucket[s[i]];
                // cout << i << " " << bucket[s[i]] << endl;
            }
        }
        else bucket[s[i]] = i; //记录第一个出现这个余数的位置
    }
    cout << ans;
    return 0;
}
