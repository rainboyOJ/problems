#include <iostream>
 
using namespace std;
const int maxn=1e5+5;
int a[maxn];
int main(){
    int n;
    cin>>n;
    int lst=0;
    int ans=0;
    for(int i=0;i<n;i++){ //边读取边做
        int now;
        cin>>now;
        if(now>lst)
            ans+=now-lst;
        lst=now;
    }
    cout<<ans<<endl;
    return 0;
}

