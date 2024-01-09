#include <bits/stdc++.h>
using namespace std;

int k,n1,n2,n3,n4,n5;
int a,b,c,d,e;
bool check(int x){
    b = x - n1*a;
    c = x - n2*b;
    d = x - n3*c;
    e = x - n4*d;
    if( e*n5 + a == x){
        if( b < 0 || c < 0 || d <0 || e <0)
            return 0;
        vector<int> t = {a,b,c,d,e};
        sort(t.begin(),t.end());
        if( unique(t.begin(), t.end()) == t.end())
            return 1;

    }
    return 0;
}
int main(){
    scanf("%d",&k);
    k *= 100;
    int i;
    scanf("%d%d%d%d%d",&n1,&n2,&n3,&n4,&n5);    
    for(i=1;i<=k;i++){
        for(a=0;a<=i;a++){
            if( check(i)){
                printf("%d %d %d %d %d %d\n",i,a,b,c,d,e);
                return 0;
            }
        }
    }
    printf("not found");
    return 0;
}
