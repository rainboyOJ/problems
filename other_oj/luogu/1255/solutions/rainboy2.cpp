#include <iostream>
#include <cstring>
using namespace std;

int n;
struct number {
    int len;
    int a[2005];

};
number num[50005];

void add(number & to,number &s1 ,number & s2)
{
    int l = max(s1.len,s2.len);
    for(int i = 0 ; i< l;i++)
    {
        to.a[i] += s1.a[i] + s2.a[i];
        to.a[i+1] += to.a[i] /10;
        to.a[i]  %= 10;
    }
    

    to.len = l;
    if( to.a[l] != 0)
    {
        to.len++;
    }

}

void fib(int dep){
    if( num[dep].len !=0)
        return;
    fib(dep-1);
    fib(dep-2);
    add(num[dep],num[dep-1],num[dep-2]);
}


int main () {
    std::cin >> n;
    num[0].len = 1;
    num[0].a[0] = 1;

    num[1].len = 1;
    num[1].a[0] = 1;

    fib(n);

    // for(int n=0;n<=10;n++)
    // {
    //     cout << n << " : " ;
    //
    //     for(int i = num[n].len-1;i >=0;--i)
    //         cout << num[n].a[i] ;
    //     cout << endl;
    // }
    for(int i = num[n].len-1;i >=0;--i)
        cout << num[n].a[i] ;

    return 0;
}
