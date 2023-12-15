#include <cstdio>
#include <cstring>

long long a;
int main(){
    scanf("%lld",&a);
    printf("%lld ",a);
    if( a < 7960)
        printf("0");
    else if( a >= 7960 && a < 11200)
        printf("1");
    else if( a >= 11200 && a < 16700)
        printf("12");
    else if( a >= 16700&& a < 115000)
        printf("123");
    else if( a >= 115000&& a < 2000000)
        printf("1234");
    else
        printf("12345");
    return 0;
}
