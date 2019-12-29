#ifndef __OPERATION__
#define __OPERATION__
#include <iostream>
#include  <string>
using namespace std;
class operation
{
    public:
        double numA;
        double numB;
        double result;
    public:
       operation(double a = 0 , double b = 0):numA(a),numB(b){}
       virtual double getResult() = 0 ;
       void print()
       {
           cout<<"result = "<<result<<endl;
       }
};
class addtion:public operation
{
    double getResult();
};
class subtraction:public operation
{
    double getResult();
};
class multiplication:public operation
{
    double getResult();
};
class division:public operation
{
    double getResult();
};
class square:public operation
{
    double getResult();
};
#endif