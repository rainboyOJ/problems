#include <cstdio>
#include <cstring>


char str[1000];
int chance[100] = {0};
int m,n;
int stay; //留下来的人数 
int main(){
    scanf("%d",&m);
    stay  = m;
    int i,t;
    for(i=1;i<=m;i++){
        scanf("%d",&t);
        if( t == 0)
            chance[i]  = 1; //女生多一次机会
    }

    scanf("%d",&n);
    // let's game start
    if( stay == 1){ //如果只有一个人
        printf("%d",1);
        return 0;
    }
    int j;

    int pre_num = 0; //上一次报的数字
    while(stay > 1){
        for(i = 1;i<=m;i++){
            if( chance[i] != -1){ //还在
                int now_num = pre_num +1;
                pre_num = now_num;

                if( now_num == n){ //是选中的那个数字 
                    chance[i]--;
                    pre_num = 0;
                }

                if(chance[i] == -1)
                    stay--;     //减少一个人
                if(stay == 1){ //是不是只有一个人了
                    for(j=1;j<=m;j++)
                        if( chance[j] != -1){
                            printf("%d",j);
                            return 0;
                        }
                }
            }
        }
    }

    for(i=1;i<=m;i++)
        if( chance[i] != -1){
            printf("%d",i);
            break;
        }
    return 0;
}
