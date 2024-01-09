#include <bits/stdc++.h>
using namespace std;
int n;
typedef map<int,int> M;
M m;


void set_m(int cnt,int id){
    int val = m[cnt];
    if(val == 0){
        m[cnt] = id;
    }
    else {
        m[cnt] = min(id,val);
    }


}

int main(){
    scanf("%d",&n);
    int i,j,t1,t2;
    m[1000000000] = 1;
    M::iterator iter1,iter2;
    for (i=1;i<=n;i++){
        scanf("%d%d",&t1,&t2);
        iter2 = m.lower_bound(t2);

        if( iter2 == m.begin()){
            printf("%d %d\n",t1,iter2->second);
            set_m(t2, t1);
        }
        else if( iter2 == m.end()){
            printf("%d %d\n",t1,(--iter2)->second);
            set_m(t2, t1);
        }
        else {
            int right = iter2->first - t2;
            int left  = t2 - (--iter2)->first;
            if( right < left)
                printf("%d %d\n",t1,(++iter2)->second);
            else if( left < right)
                printf("%d %d\n",t1,(iter2)->second);
            else {
                int a1 = iter2->second;
                int a2 = (++iter2)->second;
                printf("%d %d\n",t1,min(a1,a2));
            }
            set_m(t2, t1);
        }

    }
    return 0;
}
