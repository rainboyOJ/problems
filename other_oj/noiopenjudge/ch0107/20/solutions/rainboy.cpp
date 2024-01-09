#include <cstdio>
#include <cstring>

char str1[1000];

int main(){
    scanf("%s",str1+1);
    int len = strlen(str1+1);

    char a = str1[len-2];
    char b = str1[len-1];
    char c = str1[len];

    if( b == 'e' && c == 'r'){
        str1[len-1] = '\0';
    }
    else if (   b == 'l' && c == 'y'){
        str1[len-1] = '\0';
    }
    else if ( a == 'i' && b == 'n' && c == 'g')
        str1[len-2] = '\0';
    printf("%s\n",str1+1);
    return 0;
}


