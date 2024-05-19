#include <iostream>
using namespace std;
int a[100];
    int n;

int nixv(){
    int cnt = 0;
    for(int i = 1;i <=n ;++i ) // i: 1->n
    {
        for(int j =1;j < i ;++j ) // j: 1->i
        {
            if(a[j] > a[i])
                cnt++;
        }
    }
    return cnt;
}

void bubble() {
    for(int i = 1;i < n ;++i ) // i: 1->n
    {
        if( a[i] > a[i+1])
            swap(a[i],a[i+1]);
    }
}
void print_arr() {
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

//求逆序对数量
int main (int argc, char *argv[]) {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        cin >> a[i];
    }
    print_arr();
    cout << nixv() << endl;
    cout <<"--------" << endl;
    for(int i =1;i<n;i++)
    {
        bubble();
        print_arr();
        cout << nixv() << endl;
        cout <<"--------" << endl;
    }

    return 0;
}
