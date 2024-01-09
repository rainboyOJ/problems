#include <cstdio>
#include <cstring>


char email[500];

int n;
char str1[500];
char str2[500];
char str3[500];

int main(){
    scanf("%s",email);
    scanf("%d",&n);
    int i,j;
    int cnt=0;
    for (i=1;i<=n;i++){
        scanf("%s",str1);
        scanf("%s",str2);
        scanf("%s",str3);


        if( strcmp(str3,email) == 0){
            cnt++;
            printf("%s ",str1);
            int len = strlen(str2);
            for (j=0;j< len;j++){
                char c  = str2[j];
                if( c >='a' && c <='z'){
                    printf("%c",c+'A'-'a');
                }
                else if(  c >='A' && c <='Z')
                    printf("%c",c+'a'-'A');
                else
                    printf("%c",c);
            }
            printf("\n");
        }
    }
    if(!cnt){
        printf("empty");
    }
    return 0;
}


