/* 
三角形的三个顶点坐标求其面积的公式为:
S=(1/2)*(x1y2+x2y3+x3y1-x1y3-x2y1-x3y2)
 * */
#include <cstdio>

int main(){
    double x1,y1,x2,y2,x3,y3;
    scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3);
    double ans = (x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2)/2;
    printf("%0.2lf\n",ans);
    return 0;
}

