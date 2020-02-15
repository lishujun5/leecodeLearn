#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;
class Solution {
public:
    string decodeString(string s) 
    {
        int startNum = 0;
        return decode(s,startNum);
    }
    string decode(string& s , int& num)
    {
        string ret;
        string nxtStr;
        int countNum = 0;
        while(num < s.size())
        {
            if(isdigit(s[num]))
            {
                countNum = countNum*10 + s[num++] - '0';
            }
            else if(s[num] == '[')
            {
                num++;
                nxtStr = decode(s,num);
                for(countNum ;countNum > 0;--countNum)
                {
                    ret += nxtStr;
                }
            }
            else if(s[num] == ']')
            {
                num++;
                return ret;
            }
            else
            {
                ret.push_back(s[num++]);
            }
        }
        return ret;
    }
};

int main()
{
    string s = "2[abc]3[cd]ef3[a2[c]]";
    Solution so;
    cout<<so.decodeString(s)<<endl;
    return 0;
}


/*
1.去除最小元素
*/