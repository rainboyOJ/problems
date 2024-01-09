#include <bits/stdc++.h>
#include<iostream>
#include<cmath>
using namespace std;
int main(){
    double a,b,c,x;
    std::cin >> a >> b >> c;
    if(b*b-4*a*c>0){
        cout << "x1=";
        cout << fixed << setprecision(5) 
            << (-b+sqrt(b*b-4*a*c))/(2*a);

        cout << ";x2=";
        cout << fixed << setprecision(5)  <<
                (-b-sqrt(b*b-4*a*c))/(2*a);
    }
    else if(b*b-4*a*c==0){
        std::cout << "x1=x2=" ;
        cout << fixed << setprecision(5)  <<
            (-b+sqrt(b*b-4*a*c))/(2*a);
    }
    else{
        x=-b/(2*a);
        //if(x==0.0){
            //x= -x;
        //}
        cout << "x1=";
        cout <<fixed << setprecision(5) << x;
        cout << "+";
        cout <<fixed << setprecision(5) << sqrt(4*a*c-b*b)/(2*a);
        cout <<"i;";
        cout << "x2=";
        cout <<fixed << setprecision(5) << x;
        cout << "-";
        cout <<fixed << setprecision(5) << sqrt(4*a*c-b*b)/(2*a);
        cout <<"i";
    }
    return 0;
}
