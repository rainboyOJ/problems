/* 
 * 计算有多少个不同的符号三角形，使其所含”+“ 和”-“ 的个数相同
 * */
/* 生成 打表 结果 如下 */
/*
 *#include <bits/stdc++.h>
 *using namespace std;
 *
 *
 *int n;
 *
 *int get_num_of_sub(int len,int x){
 *    bitset<30> bit(x);
 *    int i,cnt= 0;;
 *    for(i=len;i>=1;i--){
 *        cnt += bit.count();
 *        bit = bit ^ (bit >>1);
 *        bit.reset(i-1);
 *    }
 *    return cnt;
 *}
 *
 *int sum[100]={0};
 *int ans[100];
 *int main(){
 *    int i;
 *    for(i=1;i<=24;i++){
 *        sum[i] =sum[i-1] +i;
 *    }
 *
 *    for( n =1;n<=24;n++){
 *
 *        if( sum[n] % 2 !=0 ){
 *            ans[n] = 0;
 *            continue;
 *        }
 *
 *        int i;
 *        int cnt = 0;
 *        for(i=0;i<(1<<n);i++){
 *            int num = get_num_of_sub(n, i);
 *            if( num == sum[n]>>1){
 *                cnt++;
 *            }
 *        }
 *        ans[n] = cnt;
 *    }
 *
 *    printf("int ans[25] = {0,");
 *    for(i=1;i<=24;i++)
 *        printf("%d,",ans[i]);
 *    printf("}");
 *
 *    return 0;
 *}
 */

#include <bits/stdc++.h>
using namespace std;

int ans[25] = {0,0,0,4,6,0,0,12,40,0,0,171,410,0,0,1896,5160,0,0,32757,59984,0,0,431095,822229};

int main(){
    int n;
    while (1) {
        scanf("%d",&n);
        if( n == 0) break;
        printf("%d %d\n",n,ans[n]);
    }
    return 0;
}
