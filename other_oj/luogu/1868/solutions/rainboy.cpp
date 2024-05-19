//f [i] = f[i-1] or max(f[i-1],f[j-1]+r-j+1)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e6+5;
typedef std::pair<int,int> pa;

int n;
pa a[maxn];
int f[maxn];

int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> a[i].second;
        cin >> a[i].first;
        a[i].second++;
        a[i].first++;
    }
    std::sort(a+1,a+1+n);

    int lst = 1; //上一个选取的区间
    for(int i = 1;i<maxn;i++){

        //不选
        f[i] = max(f[i],f[i-1]);

        //等于某个结束的位置
        // 可能有多个
        while( i == a[lst].first) { 
            int end = a[lst].first;
            int sta = a[lst].second;
            //选这个区间
            f[i] = max(f[i],f[sta-1] + end - sta +1);
            lst++;
        }

    }
    cout << f[maxn-1] << endl;

    return 0;
}


