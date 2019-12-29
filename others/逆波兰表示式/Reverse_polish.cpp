#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "operation.h"
#include "operationCreator.h"
using namespace std;
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string> data;
        operationCreator oper;
        for(vector<string>::const_iterator cur = tokens.cbegin() ; cur != tokens.cend() ; cur++)
        {

            if(*cur == string("+") || *cur == string("-") || *cur == string("*") || *cur == string("/"))
            {
                if(data.size() >=2 )
                {
                    operation *opt = oper.operationCreat(*cur);
                    opt->numB = atoi(data.top().c_str());
                    data.pop();
                    opt->numA = atoi(data.top().c_str());
                    data.pop();
                    char tmp[24];
                    itoa(opt->getResult(),tmp,10);
                    data.push(tmp);
                }
                else
                {
                    cerr<<"wrong Reverse polish"<<endl;
                    return -1;
                }
            }
            else
            {
                data.push(*cur);
            }
        }
        return data.size() == 1?atoi(data.top().c_str()):-1;
    }
};
int main()
{
    Solution so;
    vector<string> s= {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    cout<<so.evalRPN(s)<<endl;
}