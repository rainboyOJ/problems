#include <bits/stdc++.h>
using namespace std;

bool a[10005];
vector<int> prime;

/* 素数表 */
void shai(){

    int i,j;
    for(i=2;i<=10000;i++){
        if( !a[i])
            prime.push_back(i);
        for(j=i+i;j<=10000;j+=i){
            a[j] = 1;
        }
    }
}

int main(){
    int s;
    scanf("%d",&s);
    shai();
    int n = prime.size();
    int i,j;
    int ans = 0;
    for(i=0;i<n;i++){
        for(j=i;j<n;j++){
            if( prime[i] + prime[j] == s){
                ans = max(ans,prime[i]*prime[j]);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
