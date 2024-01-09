#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e2+5;
const int inf = 0x7fffffff;

int f[maxn][maxn][maxn];
/* 
 * pre_sum[i][j] 第i列,j个元素
 * i : 列
 * j : 行
 * */
int pre_sum[maxn][maxn];
int _map[maxn][maxn];
int n;

void init(){
    scanf("%d",&n);
    int i,j,k;
    memset(pre_sum,0,sizeof(pre_sum));
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%d",&_map[i][j]);
        }
    }

    for(j=1;j<=n;j++){ //列
        for(i=1;i<=n;i++){ //行
            pre_sum[i][j] = pre_sum[i][j-1] + _map[j][i];
        }
    }
}

/* i:第i 行 开始
 * j: 第j行 结束
 * k: 第k列
 * */
int sum(int i,int j ,int k){
    return pre_sum[k][j] - pre_sum[k][i-1];
}

int main(){
    init();
    int i,j,k;
    int ans = -inf;

    for(i=1;i<=n;i++){
        for(j=i;j<=n;j++){
            for(k=1;k<=n;k++){
                if(f[i][j][k-1] >= 0){
                    f[i][j][k] = f[i][j][k-1] +sum(i,j,k);
                }
                else
                    f[i][j][k] = sum(i,j,k);
                ans = max(f[i][j][k],ans);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
