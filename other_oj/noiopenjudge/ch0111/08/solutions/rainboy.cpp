#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000005];

int main(){
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    int pos = unique(a+1, a+n+1)-(a+1);
    for(i=1;i<=pos;i++)
        printf("%d ",a[i]);
    return 0;
}
