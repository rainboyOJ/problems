#include <bits/stdc++.h>
using namespace std;

// a[1]
char a[100];
char b[100];
int main() {
    cin >> a+1; //
    cin >> b+1;

    // la -> length a
    //strlen string length
    int la = strlen(a+1);
    int lb = strlen(b+1);

    int n1 = 1;
    int n2 = 1;

    for(int i =1;i<=la;i++) {
        int t = a[i] - 'A' +1;
        n1 *= t;
    }

    for(int i =1;i<=lb;i++) {
        int t = b[i] - 'A' +1;
        n2 *= t;
    }

    if( n1 % 47 == n2 % 47)
        cout << "GO";
    else
        cout << "STYAY";

    return 0;    
}

