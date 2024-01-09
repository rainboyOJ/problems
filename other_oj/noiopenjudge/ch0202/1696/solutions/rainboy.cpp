#include <bits/stdc++.h>
using namespace std;
#define F(n) for(int i =1;i<=n;i++)

double calc() {
    string s;
    cin >> s;
    if( s[0] == '*'){
        return calc() * calc();
    }
    else if( s[0] == '-'){
        return calc() - calc();
    }
    else if( s[0] == '+'){
        return calc() + calc();
    }
    else if( s[0] == '/'){
        return calc() / calc();
    }
    else {
        return std::stod(s);
    }
}
int main(){
    double ans = calc();
    printf("%f\n",ans);
    return 0;
}