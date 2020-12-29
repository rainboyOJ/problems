/* author: Rainboy email: rainboylvx@qq.com  time: 2020年 12月 28日 星期一 15:19:51 CST */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5,maxe = 1e6+5; //点与边的数量

int n,m;
int mod;

//===================== 线段树 BEG
template<typename T=int,int N=maxn>
struct sgt_range {
    T tr[N*4+5];
    T fx[N*4+5]; //flag1 乘法标记 默认为1
    inline int lp(int p){return p<<1;}
    inline int rp(int p){return (p<<1)|1;}
    inline int mid(int l,int r){return (l+r)>>1;}

    sgt_range(){
        for(int i=0;i<=N;++i){ fx[i] = 1; }
    }

    inline void pushup(int p){  //向上合并
        tr[p] = tr[lp(p)] + tr[rp(p)];
        tr[p] %= mod;
    }
    inline void pushdown_opt_fa(int p,int x){
        fx[p] *= x; //乘法标记 更新
        fx[p] %= mod;
        tr[p] *= x; 
        tr[p] %= mod;
    }
    inline void pushdown(int p,int m){ //向下压标记
        if( fx[p] != 1 ){ //先push 乘法
            pushdown_opt_fa(lp(p),fx[p]);
            pushdown_opt_fa(rp(p),fx[p]);
            fx[p] = 1;
        }
    }

    void build(int l,int r,int p){ //建立
        if( l == r ) {
            scanf("%lld",&tr[p]);
            return;
        }
        int m = mid(l,r);
        build(l,m,lp(p));
        build(m+1,r,rp(p));
        pushup(p);
    }

    // 区间更新
    void update(int L,int R,T v,int l,int r,int p){ 
        if(L <= l && r <= R) { //给一个新的标记
            fx[p] *= v;
            fx[p] %= mod;
            tr[p] *= v;
            tr[p] %= mod;
            return;
        }
        pushdown(p,r-l+1); //路过
        int m = mid(l,r);
        if( L<=m) 
            update(L,R,v,l,m,lp(p));
        if( R>=m+1)
            update(L,R,v,m+1,r,rp(p));
        pushup(p);
    }

    //区间查询
    T query(int L,int R,int l,int r,int p){
        if( L <=l && r<=R ) {
            return tr[p] % mod;
        }
        pushdown(p, r-l+1);
        int m = mid(l,r);
        T ret = 0;
        if( L <= m ) {
            ret+=query(L,R,l,m,lp(p));
            ret %= mod;
        }
        if( R >=m+1) ret+=query(L,R,m+1,r,rp(p));
        return ret % mod;
    }
};
sgt_range<ll> sgt;

//#define DEBUG
#ifdef DEBUG
template< typename Sgt>
struct Sgt_Debug {
    vector<string> v;
    char fmt[1000];
    Sgt &sgt;
    Sgt_Debug()=default;
    Sgt_Debug( Sgt & sgt):sgt(sgt){};
    int to_dot_cnt = 0;
    void to_dot (char *title = "") {
        v.clear();
        ofstream dot;
        sprintf(fmt,"%04d.dot",++to_dot_cnt);
        dot.open(fmt);
        dot << "graph g{\n node[shape=record];\n";
        dot << "label=\"" + string(title) + "\";\n";
        dfs_sgt(1,n,1);
        for (auto& e : v) {
            dot<< e;
        }
        dot<< "}" <<endl;
        dot.close();
    }
    void dfs_sgt(int l,int r,int p) {
        sprintf(fmt,"%d[label=\"%d|fa=%d|fx=%d|%d|%d\"];\n",p,sgt.tr[p],sgt.fa[p],sgt.fx[p],l,r);
        v.push_back(string(fmt));

        if( l == r) return ;

        int m = sgt.mid(l,r);
        sprintf(fmt,"%d--%d;\n",p,sgt.lp(p));
        v.push_back(string(fmt));
        dfs_sgt(l,m,sgt.lp(p));
        sprintf(fmt,"%d--%d;\n",p,sgt.rp(p));
        v.push_back(string(fmt));
        dfs_sgt(m+1,r,sgt.rp(p));
    }
};
Sgt_Debug< decltype(sgt)> sgt_d(sgt);
#endif


char ttt[1000];
int main(){
    scanf("%d%d%d",&n,&m,&mod);
    sgt.build(1,n,1);
    //sgt_d.to_dot("创建完成");
    for(int i=1;i<=m;++i){
        int o,x,y,z;
        scanf("%d",&o);
        if( o == 1) {
            scanf("%d%d%d",&x,&y,&z);
            sgt.update(x,y,z,1,n,1);
            //sprintf(ttt,"o=%d x=%d y=%d z=%d",o,x,y,z);
            //sgt_d.to_dot(ttt);
        }
        else {
            scanf("%d%d",&x,&y);
            ll ans = sgt.query(x,y,1,n,1);
            printf("%lld\n",ans);
            //sprintf(ttt,"o=%d x=%d y=%d ",o,x,y);
            //sgt_d.to_dot(ttt);
        }
    }
    return 0;
}
