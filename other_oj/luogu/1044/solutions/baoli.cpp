#include <iostream>
using namespace std;


int seq[50]; //-1,1序列
int n;
int ans;

int seq_num_cnt(int num) {
    int cnt = 0;
    for(int i =1;i<=2*n;i++) {
        if( seq[i] == num )
            cnt++;
    }
    return cnt;
}
bool pre_sum_check() {
    int s = 0;
    for(int i =1;i<=2*n;i++) {
        s+= seq[i];
        if( s < 0) return 0;
    }
    return 1;
}

void print_seq(){
    for(int i =1;i<=2*n;i++)
        cout << seq[i] << " ";
    cout << endl;
}

void dfs(int dep) {
    if( dep > 2*n){
        
        if( seq_num_cnt(1) == n && pre_sum_check())
        {
            //调试用,输出序列
            // print_seq();
            ans++;
        }
        return ;
    }
    seq[dep]=1;
    dfs(dep+1);
    seq[dep]=-1;
    dfs(dep+1);
}

int main() {
    cin >> n;
    dfs(1);
    cout << ans << endl;

    return 0;
}
