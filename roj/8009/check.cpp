//列出有的Q的总长度
//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-12 10:25:10
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];

char s1[maxn];
char s2[maxn];
char s3[maxn];
int num_len(int n) {
    int i = 0;
    while(n) {
        i++;
        n /= 10;
    }
    return i;
}
int main (int argc, char *argv[]) {
    std::cin >> s1 >> s2;

    std::cin >> n;
    int sum = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> s3;
        int len = strlen(s3);
        sum +=  len;
    }
    cout << "sum = " << sum  << " " << num_len(sum)<< endl;

    return 0;
}
