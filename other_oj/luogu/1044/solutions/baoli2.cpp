#include <iostream>
using namespace std;


int seq[50]; //-1,1序列
int n;
int ans;

void print_seq(){
    for(int i =1;i<=2*n;i++)
        cout << seq[i] << " ";
    cout << endl;
}

// dep 深度,放到了第几步
// prea,preb 前面的dep-1步a,b共放了多少次
void dfs(int dep,int prea,int preb) {
    if( dep > 2*n){
        //调试用,输出序列
        // print_seq();
        ans++;
        return ;
    }
    if( prea < n) {
        seq[dep]=1;
        dfs(dep+1,prea+1,preb);
    }
    if( preb < n && preb+1 <= prea)
    {
        seq[dep]=-1;
        dfs(dep+1,prea,preb+1);
    }
}

int main() {
    cin >> n;
    dfs(1,0,0);
    cout << ans << endl;

    return 0;
}
