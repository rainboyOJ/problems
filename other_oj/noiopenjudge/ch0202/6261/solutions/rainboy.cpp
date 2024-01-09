#include <cstdio>
int n;
//柱子 
int pan[4][100];
int cnt[4] = {0};
char z[5];

int get_panzi_from_zhuzi(int i){
    int a = pan[i][cnt[i]];
    cnt[i]--;
    return a;
}
void put_panzi_to_zhuzi(int i,int a){
    cnt[i]++;
    pan[i][cnt[i]] =  a;
}

void put(int i,int j){
    int a = get_panzi_from_zhuzi(i);
    printf("%c->%d->%c\n",z[i],a,z[j]);
    put_panzi_to_zhuzi(j,a);
}

// x 盘子数量 a 当前 b 辅助  c 目的
void hn(int x,int a,int b,int c){
    if( x == 1){
        put(a,c);
        return ;
    }
    hn(x-1,a,c,b);
    put(a,c);
    hn(x-1,b,a,c);
}

int main(){
    scanf("%d",&n);
    int i;
    for(i=n;i>=1;i--){
        cnt[1]++;
        pan[1][cnt[1]] = i;
    }
    char str[3];
    for (i=1;i<=3;i++){
        scanf("%s",str);
        z[i] = str[0];
    }
    hn(n,1,3,2);

    return 0;
}
