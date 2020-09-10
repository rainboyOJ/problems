#include<stdio.h>
#include<string.h>
#include<string>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<ctime>
using namespace std;
int main(){
	srand(997744-time(0)*time(0));
	/*vector<string> vec;
	int tot=rand()%100400+1;
	if(tot>100000)tot=100000;
	while(tot){
		int len=rand()%tot/2+1;
		if(len>tot)len=tot;
		string tmp="";
		tot-=len;
		while(len--){
			tmp=tmp+char('a'+rand()%26);
		}
		vec.push_back(tmp);
	}
	printf("%d\n",vec.size());
	for(int i=0;i<vec.size();i++)
		cout<<vec[i]<<endl;
		*/
	printf("200\n");
	for(int i=0;i<100;i++){
		int d=rand()%5;
		if(d==0)printf("a\n");
		if(d==1)printf("b\n");
		if(d==2)printf("ab\n");
		if(d==3)printf("ba\n");
		if(d==4)printf("aba\n");
	}
	for(int i=0;i<100;i++){
		for(int j=0;j<1000;j++){
			int d=rand()%5;
			if(d==0)printf("a");
			if(d==1)printf("b");
			if(d==2)printf("ab");
			if(d==3)printf("ba");
			if(d==4)printf("aba");
		}
		printf("\n");
	}
}
