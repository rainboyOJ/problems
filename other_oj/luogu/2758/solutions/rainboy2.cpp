#include <iostream>
#include <cstring>
using namespace std;
// f(i,j) = min( 
// f(i-1,j-1), f(i-1,j) + 1 ,f(i,j-1) +1,f(i-1,j-1) +1

char a[10000];
char b[10000];

int f[2005][2005];

int main() {
    cin >> a+1;
    cin >> b+1;
    int l1 = strlen(a+1);
    int l2 = strlen(b+1);

    //边界
    for(int i =1;i<=l1;i++) f[i][0] = i;
    for(int i =1;i<=l2;i++) f[0][i] = i;

    for(int i =1;i<=l1;i++) {
        for(int j = 1;j <= l2 ;++j ) // j: 1->l2
        {
            int cnt = 0x7f7f7f7f;
            if( a[i] == b[j]) {
                cnt = min(cnt,f[i-1][j-1]);
            }
            cnt = min( cnt,f[i-1][j]+1);
            cnt = min( cnt,f[i][j-1]+1);
            cnt = min( cnt,f[i-1][j-1]+1);
            f[i][j] = cnt;
        }
    }
    cout << f[l1][l2] << endl;

    return 0;
}
