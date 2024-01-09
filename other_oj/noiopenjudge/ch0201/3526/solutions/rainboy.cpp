#include <bits/stdc++.h>
using namespace std;

int n;
int a[605];

bool vis[1005][1005] = {0};
int gcd(int a,int b){
    if( b == 0) return  a;
    return gcd( b , a %b);
}

int main(){
    scanf("%d",&n);
    int i,j,k;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    int cnt=0;
    
    for(i=1;i<n;i++){
        for(j=i+1 ;j<=n;j++){
            if( a[j] > a[i] ){
                //printf("%d %d\n",a[i],a[j]);
                int mod = gcd(a[i],a[j]);

                int up = a[i];
                int down= a[j];
                if( mod != 1){
                    continue;
                }
                

                if(vis[up][down] ==0 ){
                    cnt++;
                    //printf("==>%d %d =%d\n",a[i],a[j],cnt);
                    vis[up][down] = 1;
                }
            }
        }
    }
    printf("%d\n",cnt);
    return 0;
}
