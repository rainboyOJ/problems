#include <iostream>
using namespace std;
const int maxn = 15000;

int n;
char s[100];
int a[5];
int b[5];

//读取这三位置到数组a里
void read(int a[]) {
  cin >> s+1;
  //注意返回过来存,a[1] 是个位数
  a[3] = s[1] - '0';
  a[2] = s[2] - '0';
  a[1] = s[3] - '0';
}

//把对应的数转成基数b下的十进制数字
long long dec_on_b(int a[],int b){
  long long ans = 0;
  ans = a[3] * b*b + a[2] *b + a[1];
  return ans;
}

void find() {
    //二维for,枚举
    for(int i =10;i<=maxn;i++)
    {
      for (int j = 10; j <=maxn; j++) {
        if( dec_on_b(a,i) == dec_on_b(b,j))
        {
          cout << i << " " << j  << endl;
          return;
        }
      }
    }
}


int main () {

  cin >> n;
  while(n--){ //循环n次
    read(a);
    read(b);
    find();
  }
  return 0;
}
