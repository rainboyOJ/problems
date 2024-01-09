#include <cstdio>
#include <cstring>
#define maxn 500

int n;
char str[maxn];
char _map[maxn];

int main(){
    _map['A'] = 'T';
    _map['T'] = 'A';
    _map['G'] = 'C';
    _map['C'] = 'G';
    scanf("%s",str+1);
    int len = strlen(str+1);
    int i;
    for (i=1;i<=len;i++){
        printf("%c",_map[ str[i]] );
    }
    return 0;
}
