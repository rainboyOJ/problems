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

int duihuan(int a){
  int b = a % 10;
  return b * 10 + a /10;
}
int main () {
  for(int i =10;i<=99;i++)
  {
    int b = duihuan(i);
    if( isprime(i) && isprime(b))
      cout << i << endl;
    

  }
  
  return 0;
}
