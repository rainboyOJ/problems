#include <cstdio>

int  main(){
	int w,y;
	scanf("%d",&w);
	scanf("%c",&y);
	scanf("%c",&y);
	int h = 8;
	if( w - 1000 > 0){
		int c = w - 1000;
		h = h + (c / 500) * 4;
		if( c % 500 != 0){
			h = h +4;
		}
	}
	if( y == 'y')
		h = h + 5;
	printf("%d",h);
	return 0;
}