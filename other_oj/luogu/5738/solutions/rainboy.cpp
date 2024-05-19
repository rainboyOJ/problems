#include <iostream>
#include <iomanip>
using namespace std;

int n,m;

double get_score(){
    int _min = 11;
    int _max = -1;
    int sum = 0;
    for(int i =1;i<=m;i++)
    {
        int t;
        cin >> t;
        sum += t;
        if( _min > t) _min = t;
        if( _max < t) _max = t;
    }
    sum -= _max;
    sum -= _min;
    return sum *1.0 / (m-2);
}

int main() {
    cin >> n >> m;
    double ans = 0;
    for(int i =1;i<=n;i++){
        double t = get_score();
        if( ans< t)
            ans= t;
    }
    cout << fixed << setprecision(2) << ans;
    return 0;
}
