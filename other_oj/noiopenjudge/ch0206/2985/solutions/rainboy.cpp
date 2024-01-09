/* author: Rainboy email: rainboylvx@qq.com  time: 2022年 03月 06日 星期日 09:45:43 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
/* 定义全局变量 */

int t;
vector<int> v;
int f[1005];

int main(int argc,char * argv[]){
    std::cin >> n >> t;
    for(int i=1;i<=n;++i){
        int x;
        std::cin >> x;
        v.push_back(x);
    }
    memset(f,0,sizeof(f));
    f[0] = 1;
    for(int i = 0;i<v.size();i++){
        int num = v[i];
        for(int j=1000;j>=1;j--){
            if( j >= num && f[j-num] != -1){
                f[j] += f[j-num];
            }
        }
        //for(int j=1;j<=5;++j){
            //std::cout <<  f[j]  << " ";
        //}
        //std::cout  << std::endl;
    }
    //for(int j=1;j<=5;++j){
        //std::cout << j << " " << f[j] << std::endl;
    //}
    std::cout << f[t] ;

    return 0;
}
