//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-18 08:43:32
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m;

char a[maxn];
char b[maxn];
char c[maxn];
int la,lb,lc;

char bucket[1000];

int main () {
    cin >> a+1;
    cin >> b+1;
    cin >> c+1;
    la = strlen(a+1);
    lb = strlen(b+1);
    lc = strlen(c+1);

    int cnt = 0;
    for(int i = 1;i <= la ;++i ) // i: 1->n
    {
        char t = a[i];
        if( bucket[t] == 0 )
        {
            bucket[t] = b[i];
            cnt++;
        }
        else if( bucket[t] != b[i]){ //already have
            cout << "Failed" << endl;
            return  0;
        }
    }
    if( cnt < 26) {
        cout << "Failed" << endl;
        return  0;
    }
    // check two
    for(int i ='A';i<='Z' ; i++) {
        char t = bucket[i];
        for(int j ='A';j<='Z' ; j++) {
            if( j == i ) continue;
            if( bucket[j] == t) { // not injective function
                cout << "Failed" << endl;
                return 0;
            }
        }
    }
    for(int i = 1;i <= lc ;++i ) // i: 1->lc
    {
        cout << bucket[c[i]];
    }
    cout <<endl;
    

    return 0;
}
