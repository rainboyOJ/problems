#include <cstdio>
#include <cstring>
char str[500];
int main(){
    int cnt = 0;
    while(1){
        int ans = scanf("%s",str);
        if( ans == EOF)
            break;
        int len = strlen(str);
        int i;
        for (i=0;i<len;i++){
            if( str[i] >= '0' && str[i] <= '9')
                cnt++;
        }
    }
    printf("%d",cnt);
    return 0;
}
