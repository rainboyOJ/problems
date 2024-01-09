#include <iostream>
using namespace std;
#define F(i, s, t) for (int i = s; i <= t; ++i)
#define fenc cout << "==========\n"
#define log(a) cout << #a " = " << a << endl
#define maxn 1005
#define maxm 105
int n, m, wds[maxn], num, dicw[maxn], nowf = 1; //n words,m cidian
void init()
{
    cin >> m >> n;
    F(i, 1, n)
    cin >> wds[i];
}

void deal()
{
    F(i, 1, n)
    {
        F(j, 1, m)
        {
            if (dicw[j] == wds[i])
            {
                break;
            }                      //如果找到，直接跳过
            else if (dicw[j] == -1) //如果找到空白，填充
            {
                num++;
                dicw[j] = wds[i];
                // log(j);
                // log(dicw[j]);
                break;
            }
            else if(j==m)
            {
                if (nowf > m)
                    nowf = 1;
                dicw[nowf] = wds[i];
                // log(nowf);
                nowf++;
                // log(dicw[nowf]);
                num++;
            }
        }
    }
}

int main()
{
    for(int i=1;i<=100;++i){
        dicw[i] = -1;
    }
    init();
    deal();
    cout << num << endl;
    return 0;
}
