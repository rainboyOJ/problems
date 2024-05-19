#include <iostream>
#include <iomanip>
using namespace std;
const int maxn = 1e5+5;

int n,m; // n个球,m个相同的盒子
int rcd[maxn]; // 记录,rcd[1]=2,表示小朋友人选了球2
//int vis[maxn]; // vis[i] 表示 球i被选走了,被使用了
//不需要vis,也不需要放回球,

// comb combination的简写
// dep 深度,pre 前一个选的数
void comb(int dep,int pre) {
    if( dep > m ) {
        //输出选的球
        for(int i =1;i<=m;i++)
            cout <<  setw(3) << rcd[i] ;
        cout << endl;
        return;
    }
    for(int i = pre+1;i<=n;i++){
        rcd[dep] = i;
        comb(dep+1,i); //下一个小朋友去选
    }
}

int main()
{
    std::cin >> n >> m;
    comb(1,0);
    return 0;
}

