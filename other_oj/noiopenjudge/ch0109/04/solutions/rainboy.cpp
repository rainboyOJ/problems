#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;



int n;
struct _stu {
    char name[30];
    int qimo_chengji;
    int bianji_chengji;
    char ganbu;
    char xibu;
    int lunwen;
};

_stu stu[105];

void init(){
    
    scanf("%d",&n);
    int i;
    for (i=1;i<=n;i++){
        scanf("%s %d %d %c %c %d",stu[i].name, &stu[i].qimo_chengji, &stu[i].bianji_chengji, &stu[i].ganbu, &stu[i].xibu, &stu[i].lunwen);
        //printf("%s %d %d %c %c %d\n",stu[i].name, stu[i].qimo_chengji, stu[i].bianji_chengji, stu[i].ganbu, stu[i].xibu, stu[i].lunwen);
    }
}


int get_fen(int i){
    int t = 0;
    _stu &s = stu[i];
    if( s.qimo_chengji >80 && s.lunwen >=1)
        t+=8000;
    if( s.qimo_chengji > 85 && s.bianji_chengji>80)
        t+=4000;
    if(s.qimo_chengji > 90)
        t+=2000;
    if(s.qimo_chengji>85 && s.xibu=='Y')
        t+=1000;
    if(s.bianji_chengji > 80 && s.ganbu == 'Y')
        t+=850;
    return t;
}

int main(){
    init();
    int i;
    int m = -1;
    int idx;
    int all = 0;
    for (i=1;i<=n;i++){
        int t=  get_fen(i);
        all+=t;
        if( m < t){
            m = t;
            idx = i;
        }
    }

    printf("%s\n%d\n%d",stu[idx].name,m,all);
    
    return 0;
}