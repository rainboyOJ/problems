#include <iostream>
using namespace std;

int n,m;

int up[10005][105]; // up[i][j] 第i层 编号为j的房间是否可以上楼
int num[10005][105]; // num[i][j]第i层 编号为j的房间上的数字
int start; // 每一层开始的房间

int can_up[10005][105]; // 提取出来的能上楼的房间
int can_up_cnt[10005]; // 每一层的能上楼的房间的数量

//long long 占8个字节的整数，可以存2x10^20大的整数，
// 想一想为什么用long long 
long long sum; // int 4 ,2x10^9,long long 8 2x10^20

//专门用来读取数据的函数
void init(){
    cin >> n >> m;
    for(int i =1;i<=n;i++){ //扫描每一层
        for(int j =0;j < m;j++){
            cin >> up[i][j];
            cin >> num[i][j];
            if( up[i][j] == 1){
                can_up[i][  can_up_cnt[i]++  ] = j; // 存下来能上楼的房间
            }
        }
    }
    cin >> start;
}

void shang_lou(int ceng){
    //start
    int cnt = 0; //记录经过了多少个能上楼的房间
    int need_cnt = num[ceng][start]; //需要寻找多少个能上楼的房间
    while( 1 ) { // 无限循环
        if( up[ceng][start] == 1) // 如果这个房间能上楼
            cnt++;
        if( cnt == need_cnt) { // 数量足够了
            break;
        }
        start++; // 到这里，说明数量不足够，全局变量start增加1
        if( start == m) // 超过了m-1，到了m，说明过了最后一个房间
            start = 0; // 转圈，从头开始
    }
}

int main(){
    init(); //读取数据
    for(int i =1;i<=n;i++) { // 一层一层去上楼
        sum += num[i][start];
        //求出上一层所在的位置
        shang_lou(i);
    }
    cout << sum % 20123 << endl;
    
    return 0;
}

