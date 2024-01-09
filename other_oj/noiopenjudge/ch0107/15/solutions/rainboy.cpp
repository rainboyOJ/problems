#include <cstdio>
#include <cstring>

int n;
char str[500];
int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%s",str+1);
        int len = strlen(str+1);
        if( str[1] >='a' && str[1] <='z'){
            printf("%c",str[1]+'A'-'a');
        }
        else
            printf("%c",str[1]);

        for (j=2;j<=len;j++){
            if( str[j] >='A' && str[j] <='Z'){
                printf("%c",str[j]+'a'-'A');
            }
            else
                printf("%c",str[j]);

        }
        printf("\n");
    }
    return 0;
}


