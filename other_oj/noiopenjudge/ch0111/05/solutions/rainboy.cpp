/* 
 * 这个题目最坑的是 pi 要定义成 3.141592653589 
 * */
#include <cstdio>

#define pi 3.141592653589
#define JD 0.00001
typedef  long long ll;

ll n,f;
double m[10005];
double _max=0;

void init(){
    scanf("%lld%lld",&n,&f);
    f++;
    int i;
    double t;
    for (i=1;i<=n;i++){
        scanf("%lf",&t);
        m[i] = pi*t*t;
        if( _max < m[i])  _max = m[i];
    }
}

ll check(double  num){
    ll i,cnt = 0;
    for (i=1;i<=n;i++){
        cnt += (m[i] / num);
    }
    return cnt;
}
double first_g(double l,double r){
    double m;
    while( l + JD <  r  ) //表示l和r没有重合
    {
        m = (l+r)/2; // 取中间位置
        ll cnt = check(m);
        if(cnt >= f) //表示 [m+1,r) 满足条件
            l = m+JD;
        else
            r = m;
    }
    return l;
}
int main(){
    init();
    int i,cnt = 0;
    double ans = first_g(0,_max);
    printf("%.3lf\n",ans-JD);
    return 0;
}

