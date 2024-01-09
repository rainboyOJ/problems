#include <cstdio>
#include <cstring>
char str[500];
int idx = 1;

int main(){
    char t;
    while( scanf("%c",&t) != EOF){
        if( t == '\n' || t == '\r')
            break;
        str[idx] = t;
        idx++;
    }
    idx--;
    int i;
    for (i=1;i<idx;i++){
        //printf("%c %d\n",str[i],str[i]);
        printf("%c",str[i]+str[i+1]);
    }
    printf("%c",str[1]+str[idx]);
    return 0;
}


