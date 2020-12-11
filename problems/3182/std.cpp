#include<bits/stdc++.h>
using namespace std;
int n,m;
char a,b;
int rood[30][30];
int MAX;
void flyd()//floyd求最长路 
{
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(rood[i][k]&&rood[k][j])
                {
                    rood[i][j]=max(rood[i][j],rood[i][k]+rood[k][j]);
                    MAX=max(MAX,rood[i][j]);//如果 MAX==n-1 那么就排序成功辣（自己想想） 
                }
}
int main()
{
    while(1)
    {
        memset(rood,0,sizeof(rood));
        cin>>n>>m;
        if(!n&&!m)
            break;//嗯，退出 
        int flag=1;//十分普通的标记 
        MAX=0;//见flyd函数注释 
        for(int i=1;i<=m;i++)
        {
            scanf(" %c<%c",&a,&b);//输入 
            int from=b-'A';//强制类型转换 
            int to=a-'A';//同上 
            if(rood[to][from])//判断是否矛盾 
            {
                printf("Inconsistency found after %d relations.\n",i);
                for(int j=i+1;j<=m;j++)//吸收下面的输入 
                    scanf(" %c<%c",&a,&b);
                flag=0;//标记 
                break;//退出 
            }
            rood[from][to]=1;//标记 
            flyd();
            int head=-1;//最大的数 
            for(int i=0;i<n;i++)
            {
                int f=1;
                for(int j=0;j<n&&f;j++)
                    if(rood[j][i])
                        f=0;
                if(f)
                    head=head==-1?i:233;//如果head==-1则赋值为i，如果head！=-1，说明最大值有两个了，赋为特殊值 
            }
            if(head!=-1&&head!=233&&MAX==n-1)//判断是否合法 
            {
                for(int j=i+1;j<=m;j++)//吸收下面的输入 
                    scanf(" %c<%c",&a,&b);
                cout<<"Sorted sequence determined after "<<i<<" relations: ";
                for(int i=n-1;i>0;i--)//挨个输出 
                    for(int j=0;j<n;j++)
                        if(rood[head][j]==i)
                            cout<<char(j+'A');
                cout<<char(head+'A')<<".\n";
                flag=0;
                break;//退出 
            }
        }
        if(flag)//上面两种情况都不满足 
            puts("Sorted sequence cannot be determined.");
    }
    return 0;//Bye~Bye~ 
}
