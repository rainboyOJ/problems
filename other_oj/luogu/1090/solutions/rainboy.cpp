/* 合并果子,单调队列+类
 *
 * */


#include <cstdio>
#include <algorithm>
using namespace std;


#define maxn 10001

struct q {
    int head;
    int tail;
    int queue[maxn];

    q(){ head=tail=0; }

    void pop(){ head++; }
    int front(){ 
        if( empty()) //队列为空时,返回大值
            return 0x7f7f7f7f;
        return queue[head];
    }
    void push(int v){ queue[tail++] = v; }
    bool empty(){return head == tail;}
};

q q1,q2;
int n,ans = 0;
int main(){
    scanf("%d",&n);
    int i,j;
    for (i=1;i<=n;i++){
        int t1;
        scanf("%d",&t1);
        q1.push(t1);
    }

    sort(q1.queue,q1.queue+n);

    while(1){
        int sum = 0;
        for(i=1;i<=2;i++){
            if( q1.front() < q2.front()){
                sum += q1.front();
                q1.pop();
            }
            else {
                sum += q2.front();
                q2.pop();
            }
        }
        ans+=sum;
        if( q1.empty() && q2.empty())
            break;
        q2.push(sum);
    }
    printf("%d",ans);
    return 0;
}


