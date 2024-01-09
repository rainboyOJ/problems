#include <cstdio>
#include <cstring>

int n;
char str[2000];
int main(){
    scanf("%d",&n);
    scanf("%s",str+1);
    int len = strlen(str+1);
    int i,cnt=1;
    for (i=2;i<=len;i++){
        if( str[i] == str[i-1]){
            cnt++;
        }
        else {
            cnt = 1;
        }
        if( cnt >=n){
            printf("%c",str[i]);
            return 0;
        }
    }
    printf("No");
    return 0;
}
