#include <cstdio>

int main(){
    int a,b;
    char c;
    scanf("%d%d",&a,&b);
    scanf("%c",&c);
    scanf("%c",&c);
    int ans ;
    if( c == '*')
        ans = a*b;
    else if( c == '/' && b == 0){
        printf("Divided by zero!");
        return 0;
    }
    else if( c == '/')
        ans = a/b;
    else if (c == '+')
        ans = a + b;
    else if (c == '-')
        ans = a - b;
    else {
        printf("Invalid operator!");
        return 0;
    }
    printf("%d\n",ans);

    return 0;
}
