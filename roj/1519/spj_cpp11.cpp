#include"testlib.h"
#include<string>
#include<vector>
#include<cassert>
bool visparty[8001],visdeputy[160001];
int n,m;
std::vector<int>e[160001];
int belonging(int x){
    if(x&1)++x;
    return x>>1;
}
main(int argc, char*argv[]){
    registerTestlibCmd(argc,argv);
    if(ans.readToken()=="NIE"){
        if(ouf.readToken()!="NIE")quitf(_wa,"Expected NIE");
        quitf(_ok,"Well done!");
    }
    n=inf.readInt(1,8000),m=inf.readInt(1,20000);
    while(m--){
        int a=inf.readInt(1,2*n),b=inf.readInt(1,2*n);
        assert(a<b);
        e[a].push_back(b),e[b].push_back(a);
    }
    for(int i=1;i<=n;++i){
        int a=ouf.readInt(1,2*n),b=belonging(a);
        if(visdeputy[a])quitf(_wa,"Deputy %d, or someone, that they do not like each other, has appeared before",a);
        if(visparty[b])quitf(_wa,"Party %d has had one representative before",b);
        visdeputy[a]=visparty[b]=1;
        for(int v:e[a])visdeputy[v]=1;
    }
    quitf(_ok,"Well done!");
}