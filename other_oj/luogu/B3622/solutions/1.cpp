//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-05-05 10:33:37
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;
int a[maxn];

string ans[maxn];
int rcd[maxn];

int k;
int cnt;

void comb(int dep,int pre) {
    if( dep > k) {
        cnt++;
        for(int i =1;i<=k;i++)
        {
            // cout << rcd[i] << " ";
            ans[cnt][rcd[i]] = '1';
        }
        // std::cout  << "\n";
        return;
    }
    for(int i =pre+1; i <=n;i++) {
        rcd[dep] = i;
        comb(dep+1,i);
    }
}


int main (int argc, char *argv[]) {
    std::cin >> n;

    for(int i = 1;i <= 100005 ;++i ) // i: 1->n
    {
        ans[i] = "000000000000000000000";
    }
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        k = i;
        comb(1,0);
    }
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << "N";
    }
    std::cout << "\n";
    sort(ans+1,ans+1+cnt);
    for(int i = 1;i <= cnt ;++i ) // i: 1->n
    {
        for(int j = 1;j <= n ;++j ) // j: 1->n
        {
            // cout << ans[i][j];
            if(ans[i][j] == '0')
                std::cout << 'N' ;
            else
                std::cout << 'Y' ;
        }
        std::cout  << "\n";
    }
    return 0;
}
