#include <cstdio>

int n,m;
int w[10010];
int total = 0;
int st[110]; //每个水龙头要接的水量

int main(){
    scanf("%d%d",&n,&m);
    int nn = n;
    int i;
    for(i=1;i<=n;i++)
        scanf("%d",&w[i]);
    int head=1;

    //初始化
    for(head=1;head<=m && head <=n;head++){
        st[head] = w[head];
    }
    head = m;
    while(n>0){ //剩余人数不为0
        total++; //时间过1
        for(i=1;i<=m;i++){
            st[i]--;
            if( st[i] == 0) n--; //人数-1
            if( st[i] == 0 && head<nn){ //人接上来
                head++;
                st[i] = w[head];
            }
        }
    }
    printf("%d",total);

    return 0;
}
