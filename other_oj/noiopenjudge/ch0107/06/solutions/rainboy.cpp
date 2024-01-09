#include <cstdio>
#include <cstring>
#define maxn 500

int n;
char str[maxn];

int main(){
    scanf("%s",str+1);
    int i;
    int len = strlen(str+1);
    if( str[1] >= '0' && str[1] <='9'){
            printf("no");
            return 0;
    }
    for (i=1;i<=len;i++){
        char c = str[i];
        if( (c >= 'a' && c <='z' ) || (c >='A' && c <='Z') || c== '_' || ( str[i] >= '0' && str[i] <='9'))
            ;
        else{
            printf("no");
            return 0;
        }
    }
    printf("yes");
    return 0;
}
