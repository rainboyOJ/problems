#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

ll n,sum;
ll a[100005];
void init(){
    scanf("%lld",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    scanf("%lld",&sum);
}

//查找范围是[l,r), a[r] 永远 >= key
template <typename T>
int first_ge(T key,T a[],int l,int r){
    int m;
    while( l != r  ) //表示l和r没有重合
    {
        m = (l+r) >>1; // 取中间位置
        if( a[m] < key ) //表示 [m+1,r) 满足条件
            l = m+1;
        else
            r = m;
    }
    return l;
}

int main(){
    init();
    sort(a+1,a+n+1);
    int i;
    for(i=1;i<=n;i++){
        ll ret = sum - a[i];
        int pos = first_ge(ret,a,i+1,n+1);
        if( a[pos] == ret){
            printf("%lld %lld\n",a[i],a[pos]);
            return 0;
        }
    }
    printf("No");
    return 0;
}
