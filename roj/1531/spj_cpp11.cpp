#include"testlib.h"
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
bool vis[1996];
struct edge{
    int x,y;
    edge(int x=0,int y=0):x(x),y(y){}
}e[1996];
int cur,testcase,edgemax,edgecnt;
main(int argc, char*argv[]){
    registerTestlibCmd(argc,argv);
    for(;;){
        memset(vis,0,sizeof vis);
        bool flag=0;
        edgecnt=edgemax=0;
        int x,y;
        while(x=inf.readInt(0,44),y=inf.readInt(0,44),x||y){
            if(!flag){
                flag=1;
                cur=std::min(x,y);
            }
            int z=inf.readInt(1,1995);
            edgemax=std::max(edgemax,z);
            e[z]={x,y};
        }
        if(!flag)break;
        ++testcase;
        std::string s=ans.readString();
        if(s[0]=='R'){
            std::string t=ouf.readString();
            if(s!=t)quitf(_wa,"Expected not exist on testcase %d",testcase);
            continue;
        }
        for(int i=1;i<=edgemax;++i){
            int nowe=ouf.readInt(1,edgemax);
            if(vis[nowe])quitf(_wa,"Street %d has been visited before on testcase %d",nowe,testcase);
            vis[nowe]=1;
            if(cur==e[nowe].x)cur=e[nowe].y;
            else if(cur==e[nowe].y)cur=e[nowe].x;
            else quitf(_wa,"Street %d does not connect to junction %d on testcase %d",nowe,cur,testcase);
        }
        ouf.readEoln();
    }
    quitf(_ok,"Good job!");
}