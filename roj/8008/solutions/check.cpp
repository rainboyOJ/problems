#include <bits/stdc++.h>
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

void print(){
  //为什么这里是10,因为答案是47 35, 
  //所以我们看看前面的数据就行了
  //太多的数据,会导致大脑过载,还不如不算
  for(int i =10;i<= 50;i++) {
    cout << i << ":  ";
    cout << setw(10) << dec_on_b(a,i) << " ";
    cout << setw(10) << dec_on_b(b,i) << " ";
    if( i == 47 || i == 35) //指明答案
      cout << " <----\n";
    else
      cout << "\n";
  } 
}


int main () {

  cin >> n;
  while(n--){ //循环n次
    read(a);
    read(b);
    print();
  }
  return 0;
}
