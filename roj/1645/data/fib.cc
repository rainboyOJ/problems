#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

VI multiply (const VI &x, const VI &y){
  VI ret (4);
  ret[0] = (x[0]*y[0] + x[1]*y[2]) % 10000;
  ret[1] = (x[0]*y[1] + x[1]*y[3]) % 10000;
  ret[2] = (x[2]*y[0] + x[3]*y[2]) % 10000;
  ret[3] = (x[2]*y[1] + x[3]*y[3]) % 10000;
  return ret;
}

VVI powers (30);

int main (){

  powers[0].push_back (1);
  powers[0].push_back (1);
  powers[0].push_back (1);
  powers[0].push_back (0);

  // powers[i] = [1 1; 1 0]^(2^i)

  for (int i = 1; i < 30; i++)
    powers[i] = multiply (powers[i-1], powers[i-1]);

  while (true){
    int n;
    cin >> n;
    if (n == -1) break;

    VI mat;
    mat.push_back (1);
    mat.push_back (0);
    mat.push_back (0);
    mat.push_back (1);

    for (int i = 0; i < 30; i++){
      if (n & (1 << i)) mat = multiply (mat, powers[i]);
    }

    cout << mat[1] << endl;
  }
}
