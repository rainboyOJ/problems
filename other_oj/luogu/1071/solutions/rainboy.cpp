#include <cstdio>
#include <cstring>

char str1[500];
char str2[500];
char str3[500];
int _map[500] = {0};

int main(){
    scanf("%s",str1+1);
    scanf("%s",str2+1);
    scanf("%s",str3+1);
    int len = strlen(str1+1);
    int i,j;
    for (i=1;i<=len;i++){
        char c = str1[i];
        if(_map[c] == 0){
            _map[c] = str2[i];
        }
        else if(_map[c] != str2[i]){
            printf("Failed");
            return 0;
        }
    }
    for (i='A';i<='Z';i++){
        if( _map[i] == 0){
            printf("Failed");
            return 0;
        }
    }
    len = strlen(str3+1);
    for (i=1;i<=len;i++){
        printf("%c",_map[ str3[i]]);
    }
    return 0;

}
