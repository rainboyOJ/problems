#include <cstdio>
#include <cstring>

char s[1000];
char tmp[1000];

bool is_hui_wen(){
    int len =  strlen(tmp);
    int mid = len /2;
    int i,j;
    for (i=0;i<mid;i++){
        if( tmp[i] != tmp[len-i-1]){
            return false;
        }
    }
    return true;
}
int main(){
    scanf("%s",s+1);
    int len = strlen(s+1);
    int i,j;
    for(i=2;i<=len;i++){
        for (j=1;j<=len-i+1;j++){
            memset(tmp,0,sizeof(tmp));
            strncpy(tmp,s+j,i);
            //printf("%s\n",tmp);
            if( is_hui_wen())
                printf("%s\n",tmp);
        }
    }
    return 0;
}


