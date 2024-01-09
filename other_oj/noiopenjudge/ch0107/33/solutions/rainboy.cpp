#include <cstdio>
#include <cstring>

char s1[1005];
int main(){
    scanf("%s",s1+1);
    int len = strlen(s1+1);
    int mid = len /2;
    int i;
    for(i=1;i<=mid;i++){
        if( s1[i] != s1[len+1-i]){
            printf("no");
            return 0;
        }
    }
    printf("yes");
    return 0;
}




