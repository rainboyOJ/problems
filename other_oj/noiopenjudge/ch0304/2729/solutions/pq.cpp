#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1e5+5;



int main() {
    int a,ba;
    while( cin >> a >>ba) {

        int cnt = 1;
        std::priority_queue<long long ,std::vector<long long> , std::greater<long long>> pq;
        pq.push(a);
        while ( cnt < ba) {
            int t = pq.top();
            cout << t << " ";
            pq.pop();
            while( !pq.empty() && pq.top() == t)
                pq.pop();
            cnt++;
            pq.push(2*t+1);
            pq.push(3*t+1);
        }
        cout << endl;
        cout << pq.top() << endl;
        // break;

    }

    return 0;
}
