#include <iostream>
#include <bitset>
#include <string>
#include <queue>
using namespace std;

/* 四个方向 */
int x[] = {0,1,0,-1};
int y[] = {1,0,-1,0};
int vis[1<<16] = {0};

typedef bitset<4> sta;
sta _map[4];

void init(){
    string s;
    int i,j;
    for(i=0;i<4;i++){
        cin >> s;
        for(j=0;j<4;j++)
            if( s[j] == 'b')
                s[j] = '1';
            else
                s[j] = '0';
        _map[i] = sta(s);
    }
}

unsigned long state_num( sta arr[]){
    int left = 12;
    int i;
    int ans = 0;
    for(i=0;i<4;i++){
        ans |= ((arr[i].to_ulong()) << left);
        left -=4;
    }
    return ans;
}



struct s{
    sta state[4];
    int step;

    /* 构造函数 */
    s(sta arr[],int _step){
        int i =0;
        for(i=0;i<4;i++)
            state[i] = arr[i];
        step = _step;
    }

};
queue<s> q;

bool inline in_map(int px,int py){
    if( px >= 0 && px <4  && py >=0 && py <4)
        return true;
    return false;
}
/* 进行操作,并进行判断*/
bool opt(sta arr[],int px,int py){

    int i;
    arr[px].flip(py);
    for(i = 0;i< 4;i++){
        int nx = px+x[i];
        int ny = py+y[i];
        if( in_map(nx,ny)){
            arr[nx].flip(ny); //取反
        }
    }

    return ( 
            ( arr[0].all() &&  arr[1].all() &&  arr[2].all() &&  arr[3].all()  )
                ||
            (arr[0].none() && arr[1].none() && arr[2].none() && arr[3].none())
            );
}

void bfs(){
    /* 特殊判断 */
    
    int start = state_num(_map) ;
    if( start == 0 || start == ((1<<16)-1)){
        cout << "0" <<endl;
        return ;
    }
    q.push({ _map,0});
    vis[start] = 1;

    while( !q.empty() ){

        s u = q.front(); q.pop();
    
        int i,j,k;
        for(i=0;i<4;i++)
            for(k=0;k<4;k++){
                sta bak[4];     //复制一个新的
                for (j=0;j<4;j++){
                    bak[j] = u.state[j];
                }
                bool res = opt(bak,i,k);
                if( res){
                    cout << u.step + 1<<endl;
                    return;
                }
                if( vis[state_num(bak)] == 0){
                    vis[state_num(bak)] = 1;
                    q.push({bak,u.step+1});
                }
            }
    }
    cout << "Impossible"<<endl;
}



int main(){
    init();
    bfs();
    return 0;
}