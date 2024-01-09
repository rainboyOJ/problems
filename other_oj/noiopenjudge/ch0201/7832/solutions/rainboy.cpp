#include <bits/stdc++.h>
using namespace std;

int n,a,b;

int gcd(int a,int b){

    if( b == 0) 
        return a;
    return gcd(b,a % b);
}

int main(){
    scanf("%d%d%d",&n,&a,&b);
    double x = a*1.0/b;
    int i,j;
    int up=1,down=n;
    double pre = up*1.0 / down;
    for(i=1;i<=n;i++){
        for(j=1;j<n;j++){
            int t1 = gcd(i,j);
            if( t1 != 1) continue;

            double y = j*1.0 / i;
            if( y < x && y > pre){
                pre = y;
                up = j;
                down = i;
            }
        }
    }
    printf("%d %d\n",up,down);
    return 0;
}
