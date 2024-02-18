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

int main(int argc,char * argv[]){
    //输出数据
    int n = std::atoi(argv[1]);
    int l = std::atoi(argv[2]);
    int r = std::atoi(argv[3]);
    // std::cin >> n >> l >> r;

    out.println(n);
    //输出n个点的随机数
    for(int i=1;i<=n;++i){
        out << RND(l,r);
        // out.sp();
    }
    out.ln();
    //输出树
    // auto tr = tree(n);
    // out.println(tr);

    return 0;
}
