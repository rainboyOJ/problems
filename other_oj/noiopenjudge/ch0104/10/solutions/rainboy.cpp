#include <cstdio>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    if(( a < 60 && b >= 60) || ( b < 60 && a >= 60 ))
        printf("1");
    else
        printf("0");
    return 0;
}
