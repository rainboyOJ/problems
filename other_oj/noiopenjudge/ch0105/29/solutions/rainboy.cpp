#include <cstdio>

int main(){
    int n;
    scanf("%d",&n);
    if( n < 0){
        n = -n;
        printf("-");
    }

    bool is_first_zeor = true;
    while( n != 0){
        int ret = n % 10;
        n /= 10;
        if( ret == 0 && is_first_zeor )
            continue;
        is_first_zeor = 0;
        printf("%d",ret);
    }
    return 0;
}
