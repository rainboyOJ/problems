#include <cstdio>


int main(){
    int i,l,r;
    int cnt=0;
    scanf("%d%d",&l,&r);
    for (i=l;i<=r;i++){
        int t= i;
        while( t != 0){
            int a = t % 10;
            if( a == 2){
                cnt++;
            }
            t /= 10;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
