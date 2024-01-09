/* 
 *   快速排序本质:
 *      用key值,把数据分成两个部分,一部分比较key小,一部分比key大
 * */

#include <cstdio>

int n;

struct _stu {
    int yw,sx,yy;
    int idx; //编号
};

_stu a[10010];

// 比较两个学生的大小 , 也就是哪个应该在前面
bool greater( _stu &a,_stu &b){
    int ta = a.yy+a.yw+a.sx;
    int tb = b.yy+b.yw+b.sx;
    if( ta > tb)
        return true;
    
    if( ta == tb  && a.yw > b.yw)
        return true;
    if(ta == tb && a.yw == b.yw && a.idx < b.idx)
        return true;
    if(a.idx == b.idx)
        return true;
    return false;
}

void xchg(_stu &a,_stu &b){
    _stu t = a;
    a = b;
    b =t;
}

void quicksort(int l,int r){

    if( l >= r) return;

    _stu key = a[l];
    int i = l, j = r;
    while( i != j){
        while(greater(key,a[j]) && i < j )
            j--;
        while(greater(a[i],key) && i < j)
            i++;
        if( i < j )
            xchg(a[i],a[j]);
    }

    a[l] = a[i];
    a[i] = key;

    quicksort(l,i-1);
    quicksort(i+1,r);
}

int main(){
	scanf("%d",&n);
	int i,j;
	//输入数据
	for(i=1;i<=n;i++){
	    a[i].idx = i;
	    scanf("%d%d%d", &a[i].yw, &a[i].sx, &a[i].yy);
	}
	quicksort(1,n);

    for(i=1;i<=5;i++)
        printf("%d %d\n",a[i].idx, a[i].yy+a[i].yw+a[i].sx);
    return 0;
}
