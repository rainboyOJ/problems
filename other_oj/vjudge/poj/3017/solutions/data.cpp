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

int main(){
    //输出数据
    int n = 5;
    int I = RND(1,n);
    int h = 10;
    int r = 3;
    out.println(n,I,h,r);
    for(int i =1;i<=r;i++) {
        while(1) {
            int l = RND(1,n);
            int r = RND(1,n);
            if( l == r) continue;
            out.println(l,r);
            break;
        }
    }

    return 0;
}
