#include <bits/stdc++.h>
using namespace std;



int main(){
    int a,b,c;
    for(a=2;a<100;a++){
        for(b=a;b<100;b++){
            for(c=b;c<=100;c++){
                if( a*a +b*b == c*c){
                    printf("%d*%d + %d*%d = %d*%d\n",a,a,b,b,c,c);
                }
            }
        }
    }
    return 0;
}
