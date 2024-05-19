#include <cstdio>
#include <cstring>

int n;
int a[200];


int f[200][200] = {0}; //不用初始化边界了
int fx[200][200] = {0}; //不用初始化边界了,存最小值
int pre[200] = {0};
int ans_max = -1;
int ans_min = 0x7f7f7f7f;


int max(int a,int b){
    if( a >b ) return a;
    return b;
}

int min(int a,int b){
    if( a <b ) return a;
    return b;
}

int sum(int i,int j){
    return pre[j] - pre[i-1];
}

int main(){
    int i,j,k;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[n+i] = a[i];
    }

    int len = (n<<1)-1;
    for(i=1;i<=len;i++){
        pre[i] = pre[i-1] +a[i];
    }
    
    memset(fx,0x7f,sizeof(fx));
    for(i=0;i<=200;i++) fx[i][i] = 0;



    // 合并几堆石子
    //枚举长度
    for(i=2;i<=n;i++){ 
        for(j=1;j<=len-i+1;j++){ //枚举起点
            for(k=j;k<j+i-1;k++){//枚举分割点
             int m =  f[j][k] + f[k+1][j+i-1];

             int xiao = fx[j][k] +fx[k+1][j+i-1];

             if( f[j][j+i-1] < m) //求 max
                 f[j][j+i-1] = m;

             if( fx[j][j+i-1] > xiao) //求 max
                 fx[j][j+i-1] = xiao;
            }
            f[j][j+i-1] += sum(j,j+i-1);
            fx[j][j+i-1] += sum(j,j+i-1);
        }
    }

    for(i=1;i<=n;i++){
        if( ans_max < f[i][i+n-1])
            ans_max = f[i][i+n-1];

        if( ans_min > fx[i][i+n-1])
            ans_min = fx[i][i+n-1];
    }
    printf("%d\n",ans_min);
    printf("%d",ans_max);

    return 0;
}


