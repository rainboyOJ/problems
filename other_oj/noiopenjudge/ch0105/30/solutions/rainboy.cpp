#include <cstdio>


int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    if( n % 19 != 0){
        printf("NO");
        return 0;
    }
    int cnt = 0;
    while( n !=0){
        if( n % 10 == 3)
            cnt++;
        n /= 10;
    }
    if( cnt == k)
        printf("YES");
    else
        printf("NO");
    return 0;
}
