#include <bits/stdc++.h>
using namespace std;

int z,q,s,l;

struct person{
    char name;
    int w;
    bool operator<(person &b){
        return w < b.w;
    }
};

int main(){
    int n=5;
    for(z=1;z<=n;z++){
        for(q=1;q<=n;q++){
            for(s=1;s<=n;s++){
                for(l=1;l<=n;l++){
                    vector<int> t = { z,q,s,l };
                    sort(t.begin(),t.end());
                    if( unique(t.begin(),t.end()) == t.end()){

                        if( 
                                z+q == s+l &&
                                z+l > s+q &&
                                z+s < q){
                            person p[] = {
                                { .name='z',.w=z},
                                { .name='q',.w=q},
                                { .name='s',.w=s},
                                { .name='l',.w=l},
                            };
                            sort(p,p+4);
                            int i;
                            for(i=0;i<4;i++){
                                printf("%c %d\n",p[i].name,p[i].w*10);
                            }

                            return 0;
                        }

                    }
                }
            }
        }
    }
    return 0;
}
