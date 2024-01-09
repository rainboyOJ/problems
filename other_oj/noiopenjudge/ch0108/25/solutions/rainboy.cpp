#include <cstdio>
int n,m,a[1010][1010] = {0};
int seq[10000];
int cnt =0;

void push_bin_2_seq(int x){
    int i;
    //printf("%d\n",x);
    for(i=4;i>=0;i--){
        if( x & ( 1 << i))
            seq[cnt] = 1;
        else
            seq[cnt] = 0;
        cnt++;
    }
}
void init(){
    scanf("%d%d",&n,&m);
    int i,j;
    char t;
    scanf("%c",&t); // 略过空格

    while( scanf("%c",&t) != EOF){
        if( t == '\n' || t == '\r') break;
        int ret;
        if( t==' ')
            ret = 0;
        else
            ret = t-'A'+1;
        push_bin_2_seq(ret);
    }
}


int main(){
    init();
    int idx = 0;
    int i,j; int r1=1,r2=n,c1=1,c2=m;
    while( r1 <= r2 && c1 <= c2 && idx < cnt){

        for(j=c1;j<=c2;j++)
            a[r1][j] = seq[idx++];

        for(i=r1+1;i<=r2;i++)
            a[i][c2] = seq[idx++];

        if( r1 != r2)
            for(j = c2-1;j>=c1;j--)
                a[r2][j] = seq[idx++];


        if(c1!=c2)
            for(int i=r2-1;i>r1;i--)
                a[i][c1] = seq[idx++];
        r1++;
        r2--;
        c1++;
        c2--;
    }

    for(i=1;i<=n;i++){
        for (j=1;j<=m;j++){
            printf("%d",a[i][j]);
        }
    }
    return 0;
}
