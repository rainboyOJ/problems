#include <bits/stdc++.h>
using namespace std;

char s[500][500];
int n,m;

//方向
int fx[8][2] = {
	1,0,
	-1,0,
	0,1,
	0,-1,
	1,1,
	1,-1,
	-1,1,
	-1,-1
};
int main(){
    std::cin >> n >> m;
	int i,j,k;
	for(i=1;i<=n;i++)
        cin >> s[i]+1;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			int t = 0;
			if( s[i][j] == '*')  cout << "*";
			else {
                //枚举8个方向
				for(k=0;k<8;k++){
					int nx = i + fx[k][0];
					int ny = j + fx[k][1];
					if( s[nx][ny] == '*') t++;
				}
                std::cout << t;
			}
		}
        std::cout << "\n";
	}
	return 0;
}
