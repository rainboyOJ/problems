#include <bits/stdc++.h>
using namespace std;


int n,m;

int main(){
    scanf("%d%d",&n,&m);
    int i;
    for(i=1;i<m;i++){
        if( 
                n % i == 0 &&
                n % (m-i) == 0
                ){
            printf("%d\n",i);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
