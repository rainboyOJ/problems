#include<iostream>
using namespace std;
char a[101][101],b[101][101];
int main()
{
    int r,c,n,i,j;
    cin>>r>>c>>n;
    for(i=1;i<=r;i++)
        for(j=1;j<=c;j++)
            cin>>a[i][j];
    for(int d=1;d<=n;d++)
    {
        for(i=1;i<=r;i++)
            for(j=1;j<=c;j++)
                b[i][j]=a[i][j];
        for(i=1;i<=r;i++)
            for(j=1;j<=c;j++)
            {
                if(b[i][j]=='R'&&b[i][j+1]=='P'||b[i][j]=='R'&&b[i][j-1]=='P'||b[i][j]=='R'&&b[i-1][j]=='P'||b[i][j]=='R'&&b[i+1][j]=='P')a[i][j]='P';
                if(b[i][j]=='S'&&b[i][j+1]=='R'||b[i][j]=='S'&&b[i][j-1]=='R'||b[i][j]=='S'&&b[i-1][j]=='R'||b[i][j]=='S'&&b[i+1][j]=='R')a[i][j]='R';
                if(b[i][j]=='P'&&b[i][j+1]=='S'||b[i][j]=='P'&&b[i][j-1]=='S'||b[i][j]=='P'&&b[i-1][j]=='S'||b[i][j]=='P'&&b[i+1][j]=='S')a[i][j]='S';
            }
    }

    for(i=1;i<=r;i++)
    {
        for(j=1;j<=c;j++)
            cout<<a[i][j];
        cout<<endl;
    }
    return 0;	
}
