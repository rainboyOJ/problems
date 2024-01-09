/* 题目的意思有歧义
 * 可以得到n个矩阵，分别对n个矩阵的map[2][2]输出
 *
 * */
#include <cstdio>

#define inf 0x7f7f7f7f

int n;
int map[200][200];
void hang(int l){
    int i,j;
    for (i=1;i<=l;i++){
        int min = inf;
        for (j=1;j<=l;j++){
            if( min > map[i][j])
                min = map[i][j];
        }
        for (j=1;j<=l;j++){
            map[i][j] -=min;
        }
    }
}

void lie(int l){
    int i,j;
    for (i=1;i<=l;i++){
        int min = inf;
        for (j=1;j<=l;j++){
            if( min > map[j][i])
                min = map[j][i];
        }
        for (j=1;j<=l;j++){
            map[j][i] -=min;
        }
    }
}

void xiao(int l){
    int i,j;
    for (i=1;i<=l;i++){
        for (j=2;j<l;j++){
            map[i][j] = map[i][j+1];
        }
    }
    for (i=1;i<l;i++){
        for (j=2;j<l;j++){
            map[j][i] = map[j+1][i];
        }
    }
}

void print(int l){
    int i,j;
    for (i=1;i<=l;i++){
        for (j=1;j<=l;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    printf("========\n");
}

int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            scanf("%d",&map[i][j]);
        }
    }
    for (i=n;i>=1;i--){
        if( i == 0)
            printf("0");
        else
        printf("%d\n",map[2][2]);
        hang(i);
        lie(i);
        xiao(i);
        //print(i-1);
    }

    return 0;
}
