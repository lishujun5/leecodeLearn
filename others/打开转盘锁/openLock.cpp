#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
#include <sstream>
#include <math.h>
#include<algorithm>
#include <set>
using namespace std;
#define startString "0000"
class Solution
{
    public:
        const static string cycleString;
        int openLock(vector<string> &deadends, string target)
        {
            set<string> HasRead;
            queue<string> data;//存储遍历解锁的队列
            int level = 0;  //本次所属遍历层数
            bool hasFind = false;
            data.push(startString);
            int count = 1;
            HasRead.insert(startString);
            while( !data.empty())
            {
                int nexCount = 0;
                //cout<<HasRead.size()<<endl;
                while(count)   //添加下一层的所有节点
                {
                    bool flag = false;
                    for(vector<string>::iterator cur = deadends.begin(); cur != deadends.end();cur++) //如果是锁死密码 就跳出
                    {
                        if(data.front() == *cur)
                        {
                            count--;
                            data.pop();
                            flag = true;
                            break;
                        }
                    }
                    if(flag)
                    {
                        continue;
                    }

                    for(int i = 0 ; i < 4 ; i++)
                    {
                        string nowString = data.front();
                        string tmpString = nowString;
                        tmpString[i] = cycleString[cycleGet(tmpString[i]-'0'+1 , cycleString.size())];
                        if(HasRead.find(tmpString) == HasRead.end())
                        {
                            if(tmpString == target)
                            {
                                hasFind = true;
                                break;
                            }
                            data.push(tmpString);
                            HasRead.insert(tmpString);
                            nexCount++;
                            cout<<tmpString<<endl;
                        }
                        tmpString = nowString;
                        tmpString[i] = cycleString[cycleGet(tmpString[i]-'0'-1 , cycleString.size())];
                        if(HasRead.find(tmpString) == HasRead.end())
                        {
                            if(tmpString == target)
                            {
                                hasFind = true;
                                break;
                            }
                            cout<<tmpString<<endl;
                            HasRead.insert(tmpString);
                            data.push(tmpString);
                            nexCount++;
                        }
                        cout<<"*************************"<<endl;
                    }
                    data.pop();
                    count--;
                }
                if(hasFind == true)
                {
                    break;
                }
                level++;
                count = nexCount;
            }
            return level+1;
        }
        int cycleGet(int num , int size)
        {
            if(num>=0)
            {
                return num%size;
            }
            else
            {
                return size+num;
            }
        }
};
const string Solution::cycleString = "0123456789";
int main()
{
    vector<string> deadends{"0201" , "0101" , "0102" , "1212" , "2002"};
    string target("0202");
    Solution solution;
    cout<<solution.openLock(deadends , target)<<endl;
    return 0;
}