#include <iostream>
#include <cstring>
using namespace std;
struct person{
    string name;
    int qian;
}a[20];


int main(){
    int n,m,cnt;
    string name_in;
    string name_out;
    int i;
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i].name;
    }

    for ( i = 1; i <= n; i++)
    {
        cin>>name_out>>m>>cnt;
        if(!m||!cnt) continue;

        for ( i = 1; i <= cnt; i++)
        {
            cin>>name_in;
            for ( i = 1; i <= n; i++){
                if (name_in==a[i].name)
                {
                    a[i].qian+=m/cnt;
                    break;
                }
            }
            for ( i = 1; i <= n; i++){
                if (name_out==a[i].name)
                {
                    a[i].qian-=m;
                    a[i].qian+=m%cnt;
                    break;
                }
            }
        }
    }

    for ( i = 1; i <= n; i++)
    {
        cout<<a[i].name<<" "<<a[i].qian<<endl;
    }

}
