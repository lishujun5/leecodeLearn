#include "operationCreator.h"
operation *operationCreator::operationCreat(string strOpt)
{
    switch (strOpt.at(0))
    {
    case '+':
        opt = new addtion();
        break;
    case '-':
         opt = new subtraction();
        break;
    case '*':
         opt = new multiplication();
        break;
    case '/':
         opt = new division();
        break;
    case '^':
         opt = new square();
        break;
    default:
        cout<<"error operation"<<endl;
        opt = NULL;
        break;
    }
    return opt;
}