#include <cstdio>
typedef long long ll;
ll a,b,c;

ll f[21][21][21] = {0};

ll w(ll a,ll b,ll c){
    if( a <=0 || b <= 0 || c <=0)
        return 1;
    if( a >20 || b >20 || c >20)
        return w(20,20,20);

    if( f[a][b][c]) return f[a][b][c];

    if( a < b && b < c){
        ll ans = w(a,b,c-1) + w(a,b-1,c-1) - w(a,b-1,c);
        f[a][b][c] = ans;
        return ans;
    }
    ll ans = w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
    f[a][b][c] = ans;
    return ans;
    
}
int main(){
    while(1){
        scanf("%lld%lld%lld",&a,&b,&c);
        if( a == -1 && b == -1 && c== -1)
            break;
        printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,w(a, b,c));
    }
    
    return 0;
}


