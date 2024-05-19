#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;

char word[20];
int lenw;
int lena;
int cnt;
int first = -1;
char article[maxn];
char word2[maxn];
int idx,word_2_start;


void to_lower(char * s,int size){
    for(int i =0;i<size;i++)
        if( s[i] >='A' && s[i] <='Z')
        {
            s[i] = s[i]-'A' + 'a';
        }
}

bool is_equal() {
    for(int i =0;i<lenw;i++) {
        if( word[i] != word2[i])
            return false;
    }
    return true;
}


int main() {
    //这里使用cin.getline 一次计读取一行
    cin.getline(word,100);
    cin.getline(article,maxn);
    lenw = strlen(word);
    lena = strlen(article);

    to_lower(word,lenw);
    to_lower(article,lena);

    for(int i = 0 ;i< lena;i++) {
        if( article[i] == ' ')
        {
            if( idx != 0 && idx == lenw && is_equal() ) {
                if( first == -1) first = word_2_start;
                cnt++;
            }
            idx = 0;
        }
        else
        {
            if( idx == 0) word_2_start = i;
            word2[idx++] = article[i];
        }
    }
    if( cnt == 0)
        cout << -1;
    else
        cout << cnt << " " << first;

    return 0;
}

