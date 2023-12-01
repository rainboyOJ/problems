#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
char s[MAXN];
string s1,s2,s3,s4;
int ans;
int main()
{
    scanf("%s",s);
    for(int i=0;s[i];++i){
        if(s[i]>='a'&&s[i]<='z'){
            s1+=s[i];
        }
        else if(s[i]>='A'&&s[i]<='Z'){
            s2+=s[i];
        }
        else if(s[i]>='0'&&s[i]<='9'){
            s3+=s[i];
        }
        else{
            s4+=s[i];
        }
    }
    if(s1.size())++ans;
    if(s2.size())++ans;
    if(s3.size())++ans;
    if(s4.size())++ans;
    printf("password level:%d\n",ans);
    printf("%s\n",s1.size()?s1.c_str():"(Null)");
    printf("%s\n",s2.size()?s2.c_str():"(Null)");
    printf("%s\n",s3.size()?s3.c_str():"(Null)");
    printf("%s\n",s4.size()?s4.c_str():"(Null)");
    return 0;
}
