#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//////// 常用宏
#define F(n) for (int i = 1; i <= n; ++i)
#define FF(i, n) for (int i = 1; i <= n; ++i)
#define F3(i, s, n) for (int i = s; i <= n; ++i)

/////////////// log,调试用
#define __LOG_INFO__ "[" \
                         << "Ln " << __LINE__ << "]: "

#ifdef DEBUG
#define log(...)               \
    std::cerr << __LOG_INFO__; \
    __debug_with_arg_name(std::cerr, #__VA_ARGS__, __VA_ARGS__)
#else
#define log(...)
#endif

template <typename T1, typename... T2>
void __debug_with_arg_name(std::ostream &O, std::string args_str, T1 &&arg1)
{

    O << args_str << "=" << arg1 << '\n';
}

template <typename T1, typename... T2>
void __debug_with_arg_name(std::ostream &O, std::string args_str, T1 &&arg1, T2 &&...args)
{
    auto p1 = args_str.find_first_of(",");
    O << args_str.substr(0, p1) << "=" << arg1 << ',';
    __debug_with_arg_name(O, args_str.substr(p1 + 1), std::forward<T2>(args)...);
}
///////////////////////
const int maxn = 1e7 + 1; // 点与边的数量
int t, nx[maxn], flag;
bool bat[maxn];
/* 定义全局变量 */
bool check(int x)
{
    while (x)
    {
        if (x % 10 == 7)
            return 1;
        x /= 10;
    }
    return 0;
}
int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    F(maxn)
    {
        if (check(i))
            for (int j = i; j <= maxn; j += i)
                bat[j] = 1;
        else if (!bat[i])
        {
            F3(j, flag, i - 1)
            nx[j] = i;
            flag = i;
        }
    }
    int q;
    while (t--)
    {
        cin >> q;
        if (bat[q])
            cout << "-1" << endl;
        else
            cout << nx[q] << endl;
    }
    return 0;
}