#include <vector>
#include <iostream>
#include <random>

std::random_device rd();




int main(){
    std::default_random_engine __rnd(rd());
    return 0;
}
