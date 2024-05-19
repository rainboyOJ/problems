// 变成了一个递归 算法,
#include <iostream>
using namespace std;
int n;
int a1,a2=-1; // a2 = -1表示还没有取第n个苹果
//a1 表示取了几次
int main() {
    std::cin >> n;
    int left = n; //剩余的没有取的苹果的数量

    // 如果 还有剩余的苹果,就还要取
    for( ; left != 0; ) {
        a1++; //取的次数,加1
        int num = (left+2) / 3; //取了多少苹果
        
        //第一次,正好取到最后一个苹果
        if(a2 == -1 && (left+2) % 3 == 0) { 
            a2 = a1;

        }
        left -= num; //去除取了的苹果
    }
    cout << a1 << " " << a2 << endl;
    return 0;
}
