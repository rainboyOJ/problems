#include <bits/stdc++.h>
using namespace std;

int n;

int main(){
    scanf("%d",&n);
    int a,b,c;
    int cnt = 0;
    for(c=0;c<=n /5;c++){
        for(b=0;b<=n/2;b++){
            for(a=0;a<=n;a++){
                if( c*5 + b *2 + a == n){
                    cnt++;
                    printf("%03d%12d%12d%12d\n",cnt,a,b,c);
                }
            }
        }
    }
    return 0;
}
