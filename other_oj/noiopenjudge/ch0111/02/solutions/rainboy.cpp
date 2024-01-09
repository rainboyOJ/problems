/* author: Rainboy email: rainboylvx@qq.com  time: 2021年 04月 07日 星期三 12:53:57 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

double f(double x){
    return pow(x,5) - 15*pow(x,4) + 85*pow(x,3) - 225*pow(x,2) + 274*x -121;
}


double bs(double l,double r){
    double pc = 0.00000001;
    while (r-l > pc) {
        double m = (l+r) / 2;
        if( f(m) > 0 )
            l = m; 
        else 
            r = m;
    }
    return l;
}

int main(){
    double ans = bs(1.4,2.5);
    printf("%0.6lf",ans);
    return 0;
}
