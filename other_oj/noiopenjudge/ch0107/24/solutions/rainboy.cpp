#include <cstdio>
#include <cstring>

char str[1000];
int main(){
    scanf("%s",str);
    int len =  strlen(str);
    printf("%d",len);
    
    while(1){
        int ret = scanf("%s",str);
        if( ret == EOF) break;
        len =  strlen(str);
        printf(",%d",len);
    }
    return 0;
}


