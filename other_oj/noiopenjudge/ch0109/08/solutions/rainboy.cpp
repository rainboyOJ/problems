#include <cstdio>
#include <cmath>


int n;
double a[1000];

double max = -1;
double min =  99999;
int main(){
    scanf("%d",&n);
    int i;
    double sum = 0;
    for (i=1;i<=n;i++){
        scanf("%lf",&a[i]);
        if( max < a[i])
            max = a[i];
        if( min > a[i])
            min = a[i];
        sum += a[i];
    }

    double  max2 = -1;
    sum -=(max+min);
    int cnt_max=0,cnt_min=0;
    double level = sum /(n-2);
    for (i=1;i<=n;i++){
        if(a[i] == max && cnt_max == 0) {
            cnt_max++;
            continue;
        }
        if(a[i] == min && cnt_min== 0) {
            cnt_min++;
            continue;
        }
        double ret = fabs(a[i]-level);
        if( ret > max2){
            max2 = ret;
        }

    }
    printf("%.2lf %.2lf",level,max2);
    return 0;
}
