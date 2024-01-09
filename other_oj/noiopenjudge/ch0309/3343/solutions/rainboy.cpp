#include <bits/stdc++.h>
using namespace std;
int n;
typedef map<int,int> M;
M m;



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
            m[t2] = t1;
        }
        else if( iter2 == m.end()){
            printf("%d %d\n",t1,(--iter2)->second);
            m[t2] = t1;
        }
        else {
            int right = iter2->first - t2;
            int left  = t2 - (--iter2)->first;
            if( right < left)
                printf("%d %d\n",t1,(++iter2)->second);
            else
                printf("%d %d\n",t1,(iter2)->second);
            m[t2]= t1;
        }

    }
    return 0;
}
