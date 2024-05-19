#include <iostream>
#include <cstring> //使用字符串相关的函数
using namespace std;

char name[20][20];  //存人的名字
int name_len[20];//每个人的名字的长度
int n; //人的数量

int money[20]; //每个人的钱

//传入一个字符串,判断这个字符串对应的是第几个人
int get_id(char a[]) {
    int len = strlen(a+1);
    for(int i =1;i<=n;i++) {
        if(name_len[i] != len) continue;
        bool flag = 1;
        for(int j =1;j<=len;j++) {
            if( name[i][j] != a[j])
            {
                flag = 0;
                break;
            }
        }
        if( flag == 1) //就是这个人
            return i;
    }
    return -1; // 没有找到
}

//送钱的那个人
char giver[20];
char recive[20];


int main () {
    cin >> n;
    for(int i =1;i<=n;i++)
    {
        cin >> name[i]+1;
        name_len[i] = strlen(name[i]+1);
    }

    while(1) {
        cin >> giver+1;
        if( cin.eof()) break;
        int m; //钱
        int cnt; //给几个人
        cin >> m >> cnt;
        
        int id = get_id(giver);
        money[id] -= m;
        if( cnt != 0)
            money[id] += m % cnt;


        for(int j =1;j<=cnt;j++) {
            cin >> recive+1;
            int id = get_id(recive);
            money[id] += m / cnt;
        }
 
    }

    //输出
    for(int i =1;i<=n;i++) {
        cout << name[i]+1 << " " << money[i] << endl;
    }
    
    return 0;
}
