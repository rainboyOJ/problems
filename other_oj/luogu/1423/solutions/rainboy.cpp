#include <bits/stdc++.h>
using namespace std;
double s;
int main()
{
    cin>>s;
    if(s <= 2) //这里这样,想一想
    {
        cout<< 1; //这里输出1步,想一想为什么?
        return 0; //这里
    }
    // int a=2; // 这里不应该用int,应用用double,因为要乘以0.98
    double a = 2;

    // for(int i =1;1;i++)
    //从第2步开始,
    double pre = 2; //上一步游动的长度
    for(int i =2;1;i++)
    {
        a += pre * 0.98;
        pre = pre * 0.98; // 这一步游动了多长
        if( a >= s) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}

