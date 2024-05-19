//Author by [Rainboy](https://github.com/rainboylvx) 
//date: 2024-04-04 13:30:09
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
char a[maxn];
int len;
int bucket[maxn];

void check_boy(int i) {
    if( a[i] == 'b') {
        bucket[i] = 1;
    }
    else if ( a[i] == 'o') {
        bucket[i] = 1;
        if( i-1>0&& a[i-1] == 'b') 
            bucket[i-1] = 0;
    }
    else if ( a[i] == 'y') {
        bucket[i] = 1;
        if( i-1>0 && a[i-1] == 'o') bucket[i-1] = 0;
        if( i-2>0 && a[i-1] == 'o' && a[i-2] == 'b')
        {
            bucket[i-1] = 0;
            bucket[i-2] = 0;
        }
    }

}

void check_girl(int i) {
    if( a[i] == 'g') {
        bucket[i] = 2;
    }
    else if ( a[i] == 'i') {
        bucket[i] = 2;
        if( i-1>0&& a[i-1] == 'g') bucket[i-1] = 0;
    }
    else if ( a[i] == 'r') {
        bucket[i] = 2;
        if( i-1>0&& a[i-1] == 'i') bucket[i-1] = 0;
        if( i-2>0&& a[i-1] == 'i' && a[i-2] == 'g')
        {
            bucket[i-1] = 0;
            bucket[i-2] = 0;
        }
    }
    else if ( a[i] == 'l') {
        bucket[i] = 2;
        if( i-1>0&& a[i-1] == 'r') bucket[i-1] = 0;
        if( i-2>0&& a[i-1] == 'r' && a[i-2] == 'i')
        {
            bucket[i-1] = 0;
            bucket[i-2] = 0;
        }
        if( i-3>0&& a[i-1] == 'r' && a[i-2] == 'i' && a[i-3] == 'g')
        {
            bucket[i-1] = 0;
            bucket[i-2] = 0;
            bucket[i-3] = 0;
        }
    }
}


int main (int argc, char *argv[]) {
    cin >> a+1;
    len = strlen(a+1);
    for(int i = 1;i <= len ;++i ) // i: 1->len
    {
        check_boy(i);
        check_girl(i);
    }
    int cnt1=0;
    int cnt2=0;
    for(int i = 1;i <= len ;++i ) // i: 1->len
    {
        if( bucket[i] == 1) cnt1++;
        if( bucket[i] == 2) cnt2++;
    }
    // cout << a+1 <<endl;
    // for(int i = 1;i <= len ;++i ) cout << bucket[i];
    // cout <<endl;
    cout << cnt1 <<endl;
    cout << cnt2 <<endl;


    return 0;
}
