#include <iostream>
using namespace std;

bool isprime(int a) {
  if( a == 1) return 0;
  for(int i =2;i*i <=a ;i++)
    if( a % i ==0 ) return 0;
  return 1;
}

int n;
int cnt;
int main () {
  cin >> n;
  for(int i =2;i<=n;i++)
    if( isprime(i)) cnt++;
  cout << cnt;
  
  return 0;
}
