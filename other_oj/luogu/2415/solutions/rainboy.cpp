#include <iostream>
using namespace std;

long long sum;
long long cnt;
int main () {
  long long t;
  while(cin >> t)  {
    sum += t;
    cnt++;
  }
  cout << sum*(1 << (cnt-1));
  return 0;
}
