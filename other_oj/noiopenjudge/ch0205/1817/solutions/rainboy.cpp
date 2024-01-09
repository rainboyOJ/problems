/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 06月 13日 星期日 19:56:55 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

char mg[5000][5000];

/* 顺时针-4个方向 */
int fx[][2] = {
    {0,-1} , // 西
    {-1,0},  //北
    {0,1}, //东
    {1,0} // 南
};
int fx2[][2] = {
    {-1,-1} , // 西
    {1,1},  //北
    {-1,1}, //东
    {1,-1} // 南
};

int cnt = 0,max_cnt=0;
int cnt_room = 0;

void init(){
    scanf("%d%d",&n,&m);
    memset(mg,' ',sizeof(mg));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            int t;
            scanf("%d",&t);
            int x = i*2;
            int y = j*2;
            int nx = x  + fx[0][0];
            int ny = y  + fx[0][1];
            if( t & 1 ) mg[nx][ny] = '#'; 
            else        mg[nx][ny] = '|';

            nx = x  + fx[1][0];
            ny = y  + fx[1][1];
            if( t & 2 ) mg[nx][ny] = '#'; 
            else        mg[nx][ny] = '|';

            nx = x  + fx[2][0];
            ny = y  + fx[2][1];
            if( t & 4 ) mg[nx][ny] = '#'; 
            else        mg[nx][ny] = '|';

            nx = x  + fx[3][0];
            ny = y  + fx[3][1];
            if( t & 8 ) mg[nx][ny] = '#'; 
            else        mg[nx][ny] = '|';

            for(int i=0;i<=3;++i){
                nx = x + fx2[i][0];
                ny = y + fx2[i][1];
                mg[nx][ny] = '#';
            }

        }
    }
}

bool inmg(int x,int y){
    return x >=1 && x <=2*n+1 && y >=1 && y <=2*m+1;
}

void dfs(int x,int y){
    if( x %2 == 0 && y % 2 == 0){
        cnt++;
        mg[x][y] = '!';
    }

    for(int i=0;i<=3;++i){
        int nx = x + fx[i][0];
        int ny = y + fx[i][1];
        if( inmg(nx,ny) && mg[nx][ny] !='#' && mg[nx][ny] !='!'){
            dfs(nx,ny);
        }
    }
}
int main(){
    init();
    //for(int i=1;i<=2*n+1;++i){
        //for(int j=1;j<=2*m+1;++j){
            //printf("%c",mg[i][j]);
        //}
        //printf("\n");
    //}
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            int x = i *2;
            int y = j *2;
            cnt = 0;
            if( mg[x][y] == ' ' ){
                dfs(x,y);
                cnt_room++;
            }
            max_cnt = max(max_cnt,cnt);
        }
    }
    printf("%d\n",cnt_room);
    printf("%d",max_cnt);
    return 0;
}
