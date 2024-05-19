#include <bits/stdc++.h>
#include <vector>
#include <iostream>
// #include <cyaroncpp/cyaron.hpp>
#include "base.hpp"
#include "utils/random/tree.hpp"
using namespace __random;


template<typename... T>
void input_writeln(T&&... args){
    ( (std::cout << args<<" "),...);
    std::cout << "\n";
}

int a[1000];
int main(){
    //输出数据
    int n = 5;
    out.println(5);

    for(int i=1;i<=n;++i){
        a[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(a+1,a+1+n,g);
    out.println(a+1,a+1+n);


    return 0;
}
