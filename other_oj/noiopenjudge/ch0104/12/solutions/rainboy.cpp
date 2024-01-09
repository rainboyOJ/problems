#include <cstdio>
int main(){
    int a,b;
    scanf("%d",&a);
    double walk_time = a / 1.2;
    double bike_time = a / 3.0;
    bike_time += 23;
    bike_time += 27;
    if( bike_time == walk_time)
        printf("All");
    else if ( bike_time > walk_time)
        printf("Walk");
    else {
        printf("Bike");
    }
    return 0;
}
