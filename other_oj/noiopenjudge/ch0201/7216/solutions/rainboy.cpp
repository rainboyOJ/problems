#include <bits/stdc++.h>
using namespace std;


int main(){
    int n;
    scanf("%d",&n);

    int a,b,c ; // a * b * c == n
    int ans = 0x7f7f7f7f;
    for(a=1;a<=n;a++){
        for(b=1;b<=n;b++){
            if ( n %( a*b) == 0){
                c = n / (a*b);
                ans = min(ans,(a*b + a*c + c*b)*2);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
