#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 1e5+5;
int s,n;
char a[1005];

//bn = big_number
struct bn { 
    int len;
    int a[maxn];

    int & operator[](int id) {
        return a[id];
    }
};

// a = b+c
void bn_add( bn & a,bn &b ,bn & c) {
    //清空a的值
    memset(&a,0,sizeof(a));
    a.len = max(b.len,c.len);
    for(int i =0 ;i<a.len;i++) {
        a[i] += b[i] + c[i];
        a[i+1] = a[i] /10;
        a[i] %= 10;
    }
    if(a[a.len])
        a.len++;
}

void bn_print(bn & a) {
    for(int i = a.len-1 ;i>=0;i--) cout << a[i];
}

void str2bn(char * a,bn &b) {
    b.len = strlen(a);
    int cnt = 0;
    for(int i=b.len-1;i>=0;i--) b[cnt++] = a[i] - '0';
}

void copy( bn & a,bn &b) {
    a.len = b.len;
    for(int i = 0;i < a.len ;++i ) // i: 0->n
    {
        a[i] = b[i];
    }

}

bn b1,b2,b3;


int main () {
    cin >> s;
    std::cin >> n;
    a[0] = '1';
    str2bn(a,b1);
    str2bn(a,b2);
    str2bn(a,b3);

    for(int i = s+2;i <=n;i++) {
        bn_add(b3,b2,b1);
        copy(b1,b2);
        copy(b2,b3);
    }
    bn_print(b3);
    
    return 0;
}


