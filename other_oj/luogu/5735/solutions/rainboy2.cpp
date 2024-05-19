#include <iostream>
#include <iomanip> // 为了使用setprecision
#include <cmath> //为了使用 sqrt函数
using namespace std;

//使用struct
// 使用bing.com 搜索 points的中文含义
struct points{
    double x,y;
} ;
points p[10];

double ans;

//dis = distance 距离的意思
double dis(points a,points b)
{

    double t1 = a.x - b.x;
    double t2 = a.y - b.y;
    return sqrt( t1*t1 + t2*t2);
}

int main() {
    //读取三个点
    for(int i =1;i<=3;i++) {
        cin >> p[i].x ;
        cin >> p[i].y ;
    }

    //这是一个考点,
    // 有三个点,分别编号为 1 2 3
    // 任取 两个点,求它们之间的距离,有多少种可能性?
    // 有下面这三种选取的方案
    // 1 2
    // 1 3
    // 2 3
    // 你需要想明白,下面的两重for循环
    // 为什么对应上面的三种选取方式?
    // 想一想如果从5个不同的点取2个有多少种取法?
    for(int i =2;i<=3;i++) { //结尾
        for(int j =1;j<i;j++) //开头
        {
            ans += dis(p[j],p[i]);
        }
    }
    cout << fixed << setprecision(2) << ans;

    return 0;
}
