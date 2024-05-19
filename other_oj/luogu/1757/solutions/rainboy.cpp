#include <cstdio>
#include <cstring>

int f[1005] = {0};
struct _n {
    int w,v;
};
int head[110];
_n group[150][1005];

int m,n;
int max_group =-1;

int max(int a,int b){
    if(a < b) return b;
    return a;
}

int main(){
    int i,j,k;
    scanf("%d%d",&m,&n);
    int t1,t2,t3;
    for (i=1;i<=n;i++){
        scanf("%d%d%d",&t1,&t2,&t3);
        int t = head[t3]++;

        group[t3][t].w = t1;
        group[t3][t].v = t2;
        if( max_group < t3)
            max_group = t3;
    }

    for(k=1;k<=max_group;k++)
        for(j=m;j>=1;j--)
            for(i=0;i<head[k];i++){
                if( j >= group[k][i].w){
                    f[j] = max(f[j],f[j-group[k][i].w]+group[k][i].v);
                }
            }
    printf("%d",f[m]);

    return 0;
}

