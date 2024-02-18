#include <iostream>
using namespace std;

bool isprime(int a) {
  if( a == 1) return 0;
  for(int i =2;i*i <=a ;i++)
    if( a % i ==0 ) return 0;
  return 1;
}

bool is_huiwen(int n) {
  int a = n /100;
  int c = n % 10;
  return a == c;
}

int n;
int cnt;
int main () {
  for(int i =100;i<1000;i++)
  {
    if(isprime(i) && is_huiwen(i))
      cout << i << endl;
  }
  
  return 0;
}
