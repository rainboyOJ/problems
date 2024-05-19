#include <bits/stdc++.h>
using namespace std;

char s[10];
int main(){
    std::cin >> s;
	int i;
	int ans = 0;
	for(i=0;i<8;i++)//0->7
	{
		if( s[i] == '1')
			ans++; 
	}
    std::cout << ans << "\n";
	
	return 0;
}
