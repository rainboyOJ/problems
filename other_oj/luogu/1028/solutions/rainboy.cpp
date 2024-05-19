#include <iostream>
using namespace std;

int n;
int ans[1024];

int f(int n){
  if( n== 1) return 1;
  if( ans[n] != 0 ) return ans[n];
  ans[n] = 1;
  for(int i =1;i<=n/2;i++)
  {
    ans[n] += f(i);
  }
  return ans[n];
}

int main () {
  cin >> n;
  int ans = f(n);
  cout << ans;
  return 0;
}
