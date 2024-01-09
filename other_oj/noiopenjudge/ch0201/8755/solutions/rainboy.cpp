#include <bits/stdc++.h>
using namespace std;


int w[]= { 0,1,2,3,5,10,20 };
int cnt[10];
int vis[1005];
int sum = 0;

int main(){
    int i1,i2,i3,i4,i5,i6;
    for(i1=1;i1<=6;i1++){
        scanf("%d",&cnt[i1]);
    }
    for(i1=0;i1<=cnt[1];i1++){

        for(i2=0;i2<=cnt[2];i2++){
            for(i3=0;i3<=cnt[3];i3++){
                for(i4=0;i4<=cnt[4];i4++){
                    for(i5=0;i5<=cnt[5];i5++){
                        for(i6=0;i6<=cnt[6];i6++){
                            int t = 
                                i1 * w[1] +
                                i2 * w[2] +
                                i3 * w[3] +
                                i4 * w[4] +
                                i5 * w[5] +
                                i6 * w[6] ;
                            if( vis[t] == 0){
                                //printf("%d\n",t);
                                sum++;
                                vis[t]++;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("Total=%d\n",sum-1);
    return 0;
}
