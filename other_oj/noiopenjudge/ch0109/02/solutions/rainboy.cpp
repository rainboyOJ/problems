#include <cstdio>
#include <cstring>

using namespace std;

int n;
int fen;
char name[1000];
int max=-1;
char t[1000];
int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        scanf("%d",&fen);
        scanf("%s",t);
        if( fen > max){
            max = fen;
            strcpy(name,t);
        }
    }
    printf("%s\n",name);
    return 0;
}
