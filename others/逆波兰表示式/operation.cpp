#include "operation.h"
/*加法*/

double addtion::getResult()
{
    return numA+numB;
}
/*减法*/
double subtraction::getResult()
{
    return numA-numB;
}
/*乘法*/


double multiplication::getResult()
{
    return numA*numB;
}
/*除法*/

double division::getResult()
{
    if(numB == 0)
    {
        cout<<"divisor can,t be zero!!!"<<endl;
        return 0xff;
    }
    return numA/numB;
}
/*平方*/
double square::getResult()
{
    return numA*numA;
}