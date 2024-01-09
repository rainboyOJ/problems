#include <cstdio>

int main(){
    int a;
    scanf("%d",&a);
    int a1 = a % 10;
    a = a /10;
    int a2 = a % 10;
    a = a /10;
    printf("%d%d%d",a1,a2,a);
    return 0;
}

