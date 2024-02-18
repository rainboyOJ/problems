#include <bits/stdc++.h>
using namespace std;

int a,b,c;
int max(int a,int b,int c) {
  if( a < b) 
    a  = b;
  if( a < c)
    a = c;
  return a;
}
int main () {
  cin >> a >> b >> c;
  double m = 1.0 * max(a,b,c) / (max(a+b,b,c) * max(a,b,b+c));
  cout << fixed << setprecision(3) << m;

  return 0;
}
