#include <cstdio>
#include <cstring>
char str[50];
bool is_exists = false;

int main(){
    scanf("%s",str);
    int i,j,len = strlen(str);
    for (i=0;i<len;i++){
        str[i] -='0';
    }
    for (i=2;i<=9;i++){
        int pre = 0;
        for(j=0;j<len;j++){
            int num = pre*10+str[j];
            pre = num % i;
        }
        if( !pre){
            printf("%d ",i);
            is_exists = 1;
        }
    }
    if(!is_exists)
        printf("none");
    return 0;
}
