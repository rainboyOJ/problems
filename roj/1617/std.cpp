#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

long long n, m, k, x;
long long remainder;



long long Power(long long x, long long y, long long k)
{
    long long result = 1;
    remainder = x % k;
    while(y > 0)
    {
        if(y % 2 == 1)
            result = (result * remainder) % k;
        remainder = (remainder * remainder) % k;
        y = y / 2;        
    }
    return result;
}


int main(void)
{
//	freopen("circle.in", "r", stdin);
//	freopen("circle.out", "w", stdout);
    
    
    scanf("%lld%lld%lld%lld", &n, &m, &k, &x);
    
    long long result = Power(10, k, n);
    result = (result * m + x) % n;
    
    printf("%lld\n", result);
    
    return 0;
} 
