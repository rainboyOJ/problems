#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
int n;
string str;
int main()
{
	scanf("%d",&n);
	int len = 0;
	for(int i = 0;i < n; ++i){
		cin >> str;
		len += str.length();
	}
	cout << n << " " << len << endl;
}
