#include <iostream>
using namespace std;

char a[10000];
int n;

//从i向左走一步的位置
int go_left(int i) {
    i--;
    if( i < 1)
        i = n;
    return i;
}
//从i向右走一步的位置
int go_right(int i) {
    i++;
    if( i > n)
        i = 1;
    return i;
}

//ca = color a
// 表示a应该探索的颜色
char ca,cb;
// pa = postion a 表示a的位置
int pa,pb; 

//a,b是否停止
bool stop_a,stop_b;

//记录答案,数量
int ans;

int main (int argc, char *argv[]) {
    //读取数据与字符串
    std::cin >> n;
    cin >> a+1;

    //枚举断开的位置
    for(int i =1;i<=n;i++) {
        pa = i;
        pb = i+1;
        if( pb > n) pb = 1;

        //确定a,b的颜色
        ca = a[pa];
        cb = a[pb];
        stop_a = stop_b = 0; //初始化
        int cnt=2;
        while(1) { //不停的走

            // a走一步
            if( stop_a == false) {
                int pos = go_left(pa);
                //颜色不同
                if( a[pos] != 'w' && (ca != a[pos] && ca!='w') )
                {
                    stop_a = 1; //停止
                }
                else if( pos == pb ) {//和b的位置相同了
                    stop_a = 1; //停止
                }
                else {
                    //真正的走了一步
                    pa = pos;
                    cnt++; //记录增加1
                    if( a[pos] != 'w' )
                        ca = a[pos]; //变这个颜色
                }
            }

            // b走一步
            if( stop_b == false) {
                int pos = go_right(pb);
                //颜色不同
                if( a[pos] != 'w' && (cb != a[pos] && cb!='w') )
                {
                    stop_b = 1; //停止
                }
                else if( pos == pa ) {//和a的位置相同了
                    stop_b = 1; //停止
                }
                else {
                    //真正的走了一步
                    pb = pos;
                    cnt++; //记录增加1
                    if( a[pos] != 'w' )
                        cb = a[pos]; //变这个颜色
                }
            }

            //都停止了
            if( stop_a && stop_b)
                break;
        }
        cout << i << " " << cnt << endl;
        if( ans < cnt)
            ans = cnt;
    }
    cout << ans << endl;
    return 0;
}
