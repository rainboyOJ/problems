#include <iostream>
#include <cstring>
using namespace std;
int n,m;
const int maxn = 1e5+5;

int cnt[5];
int a[maxn];
int rcd[maxn]; //记录每个位置放哪个卡片
int ans;

void dfs(int dep) {
  if( dep > m ) {
    int s = 1;
    int tot = a[1];
    for(int i =1;i<=m;i++)
    {
      s+=rcd[i];
      tot += a[s];
      /* cout << rcd[i] << " "; */
    }
    /* cout << " tot = " << tot << endl; */
    if( tot > ans) ans = tot;
    return;
  }

  for(int i =1;i<=4;i++) {
    if( cnt[i] == 0) continue;
    rcd[dep] = i;
    cnt[i]--;
    dfs(dep+1);
    cnt[i]++;
  }
}


int main (int argc, char *argv[]) {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    int t;
    cin >> t;
    cnt[t]++;
    /* cout << t << " "; */
  }
  /* cout << endl; */

  dfs(1);
  cout << ans << endl;

  return 0;
}

