#include <iostream>
using namespace std;

//求数字a的因子和
int yinzihe(int a){
  int sum = 0;
  for(int i =1;i<a;i++)
  {
    if( a % i == 0)
      sum += i;
  }
  return sum;
}

int main () {
  for(int i =1;i<=9999;i++) {
    {
      int b = yinzihe(i);
      if( b == i) continue;
      int x = yinzihe(b);
      if(x == i)
      {
        cout << i << " " << b << endl;
        break;
      }
    }


  }
  return 0;
}
