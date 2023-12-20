#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    //定义数据
    double t;
    int n;
    //读取数据
    cin >> t >> n;

    //输出一个三位小数，表示可以获得多少毫升饮料
    cout << fixed << setprecision(3) << t / n << endl;
    // 输出一个三位小数，表示可以获得多少毫升饮料
    cout << 2*n << endl;

    return 0;
}
