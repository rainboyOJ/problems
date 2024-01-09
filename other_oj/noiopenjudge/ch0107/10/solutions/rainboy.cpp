#include <cstdio>
#include <cstring>
#define maxn 500

int n;
char str[maxn];
int idx=1;

char mi[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char ming[] = "VWXYZABCDEFGHIJKLMNOPQRSTU";

int main(){
    char t;
    int i;
    while(1){
        scanf("%c",&t);
        if( t == '\n' || t == '\r' || t == EOF)
            break;
        str[idx] = t;
        idx++;
    }
    idx--;

    for(i=1;i<=idx;i++){
        char c = str[i];
        if( c >= 'A' && c <= 'Z'){
            printf("%c",ming[ c-'A']);
        }
        else
            printf("%c",c);
    }
    return 0;
}
