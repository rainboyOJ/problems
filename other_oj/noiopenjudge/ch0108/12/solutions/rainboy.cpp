#include <cstdio>
#include <cstring>

int n;
char src[20][20];
char tmp[20][20];
char dst[20][20];

void clock(){
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            tmp[j][n-i+1] = src[i][j];
        }
    }
}

void p_t(){
    int i,j;
    printf("=====================\n");
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            printf("%c ",tmp[i][j]);
        }
        printf("\n");
    }
    printf("=====================\n");
}

void anti_clock(){
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            tmp[n-j+1][i] = src[i][j];
        }
    }
}

void trans(){
    anti_clock();
    //p_t();
    memcpy(src,tmp,sizeof(tmp));
    anti_clock();
    //p_t();
}

bool cmp(){
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if( tmp[i][j] != dst[i][j])
                return 0;
        }
    }
    return 1;
}

void init(){
    scanf("%d",&n);
    char t[20];
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            scanf("%s",t);
            src[i][j] = t[0];
        }
    }
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            scanf("%s",t);
            dst[i][j] = t[0];
        }
    }
}
int main(){
    init();
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            tmp[i][j] = src[i][j];
        }
    }
    if( cmp() ){
        printf("4");
        return 0;
    }


    clock();
    if( cmp() ){
        printf("1");
        return 0;
    }

    anti_clock();
    if( cmp() ){
        printf("2");
        return 0;
    }

    trans();
    if( cmp() ){
        printf("3");
        return 0;
    }
    printf("5");
    return 0;
}
