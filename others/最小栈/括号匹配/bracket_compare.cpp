#include <iostream>
#include <stack>
#include <string>
using namespace std;
class Solution {
public:
    bool isValid(string s) {
        stack<char> data;
        while(!s.empty())
        {
            char c = s.back();
            cout<<c<<endl;
            if(c == ')' || c == '}' || c == ']')
            {
                data.push(c);
            }
            else if(c == '(')
            {
                if(')' != data.top())
                {
                    return false;
                }
            }
            else if('{' == c)
            {
                if('}' != data.top())
                {
                    return false;
                }
            }
            else if('[' == c)
            {
                if(']' != data.top())
                {
                    return false;
                }
            }
            else
            {
                continue;
            }
            s.pop_back();
        }
        return true;
    }
};
int main()
{
    Solution sl;
    string s = "()[]dssadfsdaf()({{[]}})";
    cout<<sl.isValid(s)<<endl;


}