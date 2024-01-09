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
        if( str[i] >='a' &&  str[i] <='z' ){
            printf("%c",str[i]+'A'-'a');
        }
        else if( str[i] >='A' &&  str[i] <='Z' ) {
            printf("%c",str[i]+'a'-'A');
        }
        else
            printf("%c",str[i]);
    }
    return 0;
}

