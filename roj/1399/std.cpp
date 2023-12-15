#include<bits/stdc++.h>
using namespace std;
struct patient{
string name;
float temperature;
bool cough;}
a[300];
int n,t=0;
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {cin>>a[i].name>>a[i].temperature>>a[i].cough;}
    for(int i=0;i<n;i++)
    {
        if(a[i].temperature>=37.5&&a[i].cough)
        {cout<<a[i].name<<endl;
        t++;}
    }
    cout<<t<<endl;
    return 0;
}
