#include <iostream>
using namespace std;

int n;
//b 是否是a的因子
bool isyinzi(int a,int b)
{
  if( a % b == 0)
    return 1;
  return 0;
}
int main() {
  cin >> n;
  for (int i = 2; i <=n; i++) {
    int sum = 0;
    for(int j = 1;j < i;j++)
    {
      if( isyinzi(i,j))
        sum += j;
    }
    if( sum == i)
      cout << i << endl;
  }
  return 0;
}
