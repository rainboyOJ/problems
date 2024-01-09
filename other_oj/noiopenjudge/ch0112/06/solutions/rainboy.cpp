#include <cstdio>
#define mod 20123

int n,m,s;
struct _room {
    int up; //是否有楼梯
    int val; //门牌号
};
_room room[10005][105];

void init(){
    scanf("%d%d",&n,&m);
    int i,j,t1,t2;
    for (i=1;i<=n;i++){
        for (j=0;j<m;j++){
            scanf("%d%d",&room[i][j].up,&room[i][j].val);
        }
    }
    scanf("%d",&s);
}

int cnt= 0;
int men[10005];
int main(){
    init();
    int ans = 0;
    int i,j;
    for (i=1;i<=n;i++){
        cnt=0;
        ans = (ans + room[i][s].val) % mod;
        int first_idx = -1;
        int x = room[i][s].val;
        while(1){
            if( room[i][s].up ) break;
            s = (s+1) % m;
        }
        for (j=0;j<m;j++){
            if( room[i][j].up ){
                men[++cnt] = j;
                if( j == s) first_idx = cnt;
            }
        }
        int pos = (first_idx+x-1) % cnt;
        if( pos == 0)
            pos = cnt;
        s = men[pos];
    }
    printf("%d\n",ans%20123);
    return 0;
}