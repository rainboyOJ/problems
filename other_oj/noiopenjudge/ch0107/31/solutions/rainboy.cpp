#include <cstdio>
#include <cstring>

char s[1005];
int main(){
    scanf("%s",s+1);
    int cnt = 1;
    int len = strlen(s+1);
    int i;
    for (i=2;i<=len+1;i++){
        if( s[i] == s[i-1]){
            cnt++;
        }
        else {
            printf("%d",cnt);
            printf("%c",s[i-1]);
            cnt = 1;
        }
    }
    return 0;
}


