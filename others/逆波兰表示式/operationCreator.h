#ifndef __OPERATIONCREATOR__
#define __OPERATIONCREATOR__
#include "operation.h"
class operationCreator
{
    private:
        operation *opt;
    public:
        operation *operationCreat(string opt);
        operationCreator():opt(NULL){}
        ~operationCreator()
        {
            cout<<"delete opt"<<endl;
            if(opt)
                delete opt;
        }
};
#endif