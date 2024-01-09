#include <cstdio>

int n;
char name[10];
float w;
int k;

void init(){
    scanf("%d",&n);
}

bool jia_liu(float w,bool ke_sou){
    if ( w >= 37.5 && ke_sou){
        return true;
    }
    return false;
}
int main(){
    init();
    int i,cnt = 0;
    for (i=1;i<=n;i++){
        scanf("%s",&name);
        scanf("%f",&w);
        scanf("%d",&k);
        if( jia_liu(w,k)){
            printf("%s\n",name);
            cnt++;
        }
    }
    printf("%d\n",cnt);
    return 0;
}
