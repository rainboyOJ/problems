#include<bits/stdc++.h>
using namespace std;
int n;
int ans=0;
string a[105];
void w(int x,int y){

   for(int i=y-1;i>=0;i--){
    if(a[x][i]>='a'&&a[x][i]<='z')y--;
   }//       cout<<x<<" "<<y<<endl;
   for(int i=y;i<a[x].size();i++){
    if(a[x][i]=='*'||a[x][i]==' ')break;
    if(a[x][i]>='a'&&a[x][i]<='z'){a[x][i]='*';}
     //cout<<x<<" "<<i<<" :"<<a[x][i]<<endl;}               
       if(x==n)break;    
    if(a[x+1][i]>='a'&&a[x+1][i]<='z'){
        w(x+1,i);
        
        
    }}
//    }for(int k=1;k<=n;k++){
//             cout<<a[k]<<endl;
//         }cout<<endl;
}
int main(){
        cin>>n;
    getline(cin,a[0]);
    for(int i=1;i<=n;i++){
        getline(cin,a[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<a[i].size();j++){
            if(a[i][j]>='a'&&a[i][j]<='z'){
                w(i,j);
                ans++;
                // cout<<i<<" "<<j<<endl;
                // for(int k=1;k<=n;k++){
                //     cout<<a[k]<<endl;
                // }cout<<endl;
            }
        }
    }
    cout<<ans<<endl;
}
