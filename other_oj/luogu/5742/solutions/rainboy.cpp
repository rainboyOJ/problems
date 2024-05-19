#include <iostream>
using namespace std;

int n;
struct student {
    int id; //学号
    int score1;
    int score2;

    int zonghe() {
        return score1*7 + score2*3;
    }

    //返回总分
    int total() {
        return score1 + score2;
    }

    bool good() {
        return total() > 140 &&  zonghe() >= 800;
    }
};

student s; //定义一个变量就可以了

int main() {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> s.id;
        cin >> s.score1;
        cin >> s.score2;
        if( s.good())
            cout << "Excellent" << endl;
        else
            cout << "Not excellent" << endl;
    }

    return 0;
}
