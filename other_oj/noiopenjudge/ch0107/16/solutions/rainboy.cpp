#include <cstdio>
#include <cstring>

char str1[500];
char str2[500];
int idx1=0;
int idx2=0;
int main(){
    char t;
    while(1){
        int ret = scanf("%c",&t);
        if( t == '\n' || t == '\r' || ret == EOF)
            break;
        if( t >='A' && t <='Z') t = t+'a'-'A';
        str1[++idx1] = t;
    }
    while(1){
        int ret = scanf("%c",&t);
        if( t == '\n' || t==  '\r')
            continue;
        if( t >='A' && t <='Z') t = t+'a'-'A';
        str2[++idx2] = t;
        break;
    }

    while(1){
        int ret = scanf("%c",&t);
        if( t == '\n' || t == '\r' || ret == EOF)
            break;
        if( t >='A' && t <='Z') t = t+'a'-'A';
        str2[++idx2] = t;
    }
    int ans =  strcmp(str1+1,str2+1);
    if( ans == 0)
        printf("=");
    else if(ans < 0 )
        printf("<");
    else 
        printf(">");
    return 0;
}


