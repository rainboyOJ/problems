#include <cstdio>
#include <cstring>

char str[100005];
int cnt[500] = {0};

int main(){
    scanf("%s",&str[1]);
    int len = strlen(&str[1]);
    int i,j;
    for (i=1;i<=len;i++){
        cnt[ str[i] ]++;
    }
    for (i=1;i<=len;i++){
        if( cnt[ str[i] ] == 1){
            printf("%c\n",str[i]);
            return 0;
        }
    }
    printf("no");
    return 0;
}
