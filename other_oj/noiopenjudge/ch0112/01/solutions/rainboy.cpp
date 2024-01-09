#include <cstdio>

int a,b;
char c;

void init(){
    scanf("%d",&a);

    while(1){
        scanf("%c",&c);
        if( c != ' ')
            break;
    }

    scanf("%d",&b);
}

int suan(int a,int b,char c){
    if( c == '/')
        return a /b;
    if( c == '%')
        return a % b;
    if( c == '*')
        return a * b;
    if( c == '+')
        return a + b;
    if( c == '-')
        return a - b;
}

int main(){
    init();
    int ans = suan(a,b,c);
    printf("%d\n",ans);

    return 0;
}
