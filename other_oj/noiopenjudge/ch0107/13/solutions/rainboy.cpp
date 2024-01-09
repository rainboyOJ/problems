#include <cstdio>
#include <cstring>

char str[500];
int idx=0;
int main(){
    char t;
    while(1){
        int ret = scanf("%c",&t);
        if( t == '\n' || t == '\r' || ret == EOF)
            break;
        str[++idx] = t;
    }
    int i;
    for (i=1;i<=idx;i++){
        if( str[i] >='a' &&  str[i] >='a' ){
            printf("%c",str[i]+'A'-'a');
        }
        else
            printf("%c",str[i]);
    }
    return 0;
}

