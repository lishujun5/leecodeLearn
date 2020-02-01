#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        return dfsSum(0,nums,S,0,0);
    }
    int dfsSum(int sum , vector<int>& nums , int S , int i , int ret)
    {
        int tmpSum = 0;
        if(nums.size() > i)
        {
            tmpSum =sum + nums[i]; 
            ret = dfsSum(tmpSum,nums,S,i+1,ret);
            tmpSum = sum-nums[i];
            ret = dfsSum(tmpSum,nums,S,i+1,ret);
        }
        else
        {
            return sum == S?++ret:ret;
        }
        return ret;
    }
};
int main()
{
    Solution so;
    vector<int> nums = {1,1,1,1,1};
    int S = 3;
    int ret = so.findTargetSumWays(nums,S);
    cout<<ret<<endl;
}