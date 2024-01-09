#include <cstdio>
#include <cstring>


char str1[1000];
char str2[1000];
int main(){
    scanf("%s",str1);
    scanf("%s",str2);

    if( strstr(str1,str2) != NULL){
        printf("%s is substring of %s",str2,str1);
    }
    else if( strstr(str2,str1) != NULL){
        printf("%s is substring of %s",str1,str2);
    }
    else
        printf("No substring");

    return 0;
}

