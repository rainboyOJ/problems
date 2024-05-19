#include <iostream>
using namespace std;

typedef long long ll;
ll a,b,c;
ll t1,t2; //两个时间
ll n;
char t; //读取冒号:用,



int main() {
    //先读取一个数字,然后读取一个字符
    // 这样可以把这个字符给过滤掉
    cin >> a >> t;
    cin >> b >> t;
    cin >> c;

    t1 = a * 60*60 + b * 60 + c;

    cin >> a >> t;
    cin >> b >> t;
    cin >> c;
    t2 = a * 60*60 + b * 60 + c;

    cin >> n;

    cout << (t2-t1) * n<<endl;

    return 0;
}
