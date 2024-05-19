#include <iostream>
using namespace std;
int n;
char a[1000];
int vis[1000]; //是否已经走过
int ans; //最终的答案

char color; //状态
void clear_vis() {
    for(int i =1;i<=n;i++) vis[i] = 0;
}


// go left
int gl(int i) {
    i--;
    if( i == 0)
        i = n;
    return i;
}



// go right
int gr(int i){
    i++;
    if( i ==n+1)
        i = 1;
    return i;
}

int main (int argc, char *argv[]) {
    cin >> n;
    cin >> a+1;

    for(int i=1;i<=n;i++) {
        //枚举断开的位置
        int left = i; //左边的起始端点
        int right = gr(i); // 右边的超始端点

        int cnt = 0;
        clear_vis();
        color = 'w';


        //从左端点 开始走
        while(1) {
            //判断能否走
            if( vis[left] ) break;
            //不能走的条件
            if( color !='w' && a[left] != 'w' && a[left] != color)
                break;
            //更新状态
            if( color == 'w' && a[left] != 'w')
                color = a[left];
            vis[left] =1;
            cnt++;

            left = gl(left);
        }

        color = 'w';
        //从右端点 开始走
        while(1) {
            //判断能否走
            if( vis[right] ) break;
            //不能走的条件
            if( color !='w' && a[right] != 'w' && a[right] != color)
                break;
            //更新状态
            if( color == 'w' && a[right] != 'w')
                color = a[left];
            vis[right] =1;
            cnt++;

            right = gr(right);
        }
        if( ans < cnt)
            ans = cnt;
    }
    cout  << ans;
    

    return 0;
}
