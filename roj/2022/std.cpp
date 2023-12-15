
/*
    PROB:frac1
    ID:wanghan
    LANG:C++
*/
#include "iostream"
#include "cstdio"
#include "cstring"
#include "string"
#include "algorithm"
#include "vector"
using namespace std;
int n;
int gcd(int a,int b){
    if(b==0)  return a;
    return gcd(b,a%b);
}
struct Node{
    int x,y;
    double ans;
};
vector<Node> p;
bool cmp(Node a,Node b){
    return a.ans<b.ans;
}
int main()
{
    cin>>n;
    for(int i=0;i<=n;i++){
        for(int j=min(n,i+1);j<=n;j++){
            int x,y;
            x=i/gcd(i,j),y=j/gcd(i,j);
            Node t;
            t.x=x,t.y=y,t.ans=(double)x/(double)y;
            p.push_back(t);
        }
    }
    sort(p.begin(),p.end(),cmp);
    cout<<p[0].x<<"/"<<p[0].y<<endl;
    for(int i=1;i<p.size();i++){
        if(p[i].x==p[i-1].x&&(p[i].y==p[i-1].y)) continue;
        cout<<p[i].x<<"/"<<p[i].y<<endl;
    }
    return 0;
}
