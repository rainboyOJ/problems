#include<fstream>
#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>
using namespace std;
ofstream fscore,freport;
ifstream fin,fout,fstd;
bool Judge(double a,double b)
{
	a/=b;
	a-=1.0;
	if(a<0)
		a=-a;
	if(a<1e-6)
		return 1;
	return 0;
}
int main(int argc,char *argv[])
{
    fin.open(argv[1]);
    fout.open(argv[2]);
    fstd.open(argv[3]);
    fscore.open(argv[5]);
    freport.open(argv[6]);

    int score=atoi(argv[4]);
    double a,b;
	fout>>a;
	fstd>>b;
    fscore<<score*Judge(a,b)<<endl;

    fin.close();
    fout.close();
    fstd.close();
    fscore.close();
    freport.close();
}
