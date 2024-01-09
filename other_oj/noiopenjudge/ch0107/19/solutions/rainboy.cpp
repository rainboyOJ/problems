#include <cstdio>
#include <cstring>


char str1[500];
char str2[500];

int main(){
    scanf("%s",str1+1);
    scanf("%s",str2+1);
    int len1 = strlen(str1+1);
    int len2 = strlen(str2+1);
    
    char *s1 = str1,*s2=str2;
    if( len1 < len2){
        s1 = str2;
        s2 = str1;
    }
    len1 = strlen(s1+1);

    int i,j;
    if(  strstr(s1+1,s2+1) != NULL){
        printf("true");
        return 0;
    }
    for (i=2;i<=len1;i++){
        s1[len1+i-1] = s1[i-1];
        if( strstr(s1+i,s2+1) !=NULL){
            printf("true");
            return 0;
        }
    }
    printf("false");

    return 0;
}


