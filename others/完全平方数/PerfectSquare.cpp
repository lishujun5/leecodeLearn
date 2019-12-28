#include <iostream>
#include <queue>
using namespace std;
int main()
{
    int result = 59;
    int sum = 0;
    int level = 1;
    queue<int> data;
    data.push(0);
    int count = 1;  //记录当前层数个数
    int nxtcount = 0;
    while(!data.empty())
    {
        int cur = data.front();
        //计算并添加一层结果
        int i = 1;
        while(cur<result)
        {
            sum = cur + i*i;
            i++;
            if(sum == result)
            {
                cout<<level<<endl;
                return level;
            }
            else if(sum < result)
            {
                data.push(sum);
                nxtcount++;
            }
            else
            {
                break;
            }
        }
        data.pop();
        count--;
        if(count == 0)
        {
            level++;
            count = nxtcount;
            nxtcount = 0;
        }
    }
}