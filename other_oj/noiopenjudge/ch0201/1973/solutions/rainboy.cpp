#include <bits/stdc++.h>
using namespace std;

/* 按base进制转成 10 进制 */
int to_dec(int n,int base){
    int ret= 0;
    int x= 1;
    while(n){
        int t = n % 10;
        n /= 10;
        ret += t * x;
        x*=base;
    }
    return ret;
}

bool can_convert(int n,int base){
    while(n){

        int t = n % 10;
        n /=10;
        if( t >= base)
            return 0;
    }
    return 1;
}
int a,b,c;

int main(){
    scanf("%d%d%d",&a,&b,&c);
    int i;
    for(i=2;i<=16;i++){
        if( !can_convert(a,i) || !can_convert(b,i)  || !can_convert(c,i)  ) 
            continue;
        int t1 = to_dec(a, i);
        int t2 = to_dec(b, i);
        int t3 = to_dec(c, i);
        if( t1*t2 == t3){
            printf("%d\n",i);
            return 0;
        }
    }
    printf("%d\n",0);
    return 0;
}
