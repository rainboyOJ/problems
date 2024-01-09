#include <cstdio>
#include <cstring>

char str[5000];
int idx = 0;

char tmp[105];

int flag  = 1;
int next_word(){
    while(1){
        if(str[flag] != ' ' )
            break;
        else {
            printf(" ");
        }
        flag++;
    }

    if( flag == idx+1){
        return -1;
    }

    int cnt = 0;
    while(1) {
        if( str[flag] == ' ' || flag == idx+1){
            tmp[cnt] = '\0';
            return 0;
        }
        else {
            tmp[cnt++] = str[flag];
            flag++;
        }
    }

    return 0;
}

int main(){
    char t;
    while ( scanf("%c",&t)!=EOF) {
        if ( t == '\n' || t == '\r')
            break;
        str[++idx] = t;
    }


    while(1){
        if( next_word() == -1){
            break;
        }
        int len = strlen(tmp);
        int i;
        for (i=len-1;i>=0;i--){
            printf("%c",tmp[i]);
        }
    }
    return 0;
}

