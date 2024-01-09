#include <bits/stdc++.h>
using namespace std;

int a,b,c;
int x;

int main(){
    scanf("%d%d%d",&a,&b,&c);
    int i;
    for(i=2;i<=1000005;i++){
        int t1 = a % i;
        int t2 = b % i;
        int t3 = c % i;
        if( t1 == t2 && t2 == t3 && t1 == t3){
            printf("%d\n",i);
            return 0;
        }
    }
    return 0;
}
