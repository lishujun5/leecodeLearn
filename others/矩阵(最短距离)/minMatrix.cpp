#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;
class Solution {
    struct Point
    {
        int x;
        int y;
    };
    
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) 
    {
        for(int i = 0 ; i < matrix.size(); i++)
            {
                for(int j = 0 ; j <matrix[0].size() ; j++)
                {
                    if(matrix[j][i] == 1)
                    {
                        Point point = {i,j};
                        matrix[j][i] = bfsMatrix(matrix , point);
                        cout<<"return value = "<<matrix[i][j]<<endl;
                        cout<<"*****************"<<endl;
                    }
                }
            }
            return matrix;
    }
    int bfsMatrix(vector<vector<int>>& matrix , Point point)
    {
        queue<Point> data;
        set<int *> hadVisited;
        data.push(point);
        hadVisited.insert(&matrix[point.x][point.y]);
        int level = 1;
        int nxtLevelNum = 0;
        int curLevelNum = 1;
        while(!data.empty())
        {
            Point tmpPoint = data.front();
            cout<<"["<<tmpPoint.x<<","<<tmpPoint.y<<"]"<<endl;
            data.pop();
            curLevelNum--;
            int x = tmpPoint.x;
            int y = tmpPoint.y;
            if(x > 0 && x <= matrix[0].size()-1)         //left
            {
                 Point leftPoint = {x-1,y};
                if(matrix[y][x-1] != 0)
                {
                    if(!hadVisited.count(&matrix[leftPoint.y][leftPoint.x-1]))
                    {
                        nxtLevelNum++;
                        data.push(leftPoint);
                        hadVisited.insert(&matrix[leftPoint.y][leftPoint.x-1]);
                    }
                }
                else
                {
                    return level;
                }
            }
            if(x >= 0 && x < matrix[0].size()-1)
            {
                Point rightPoint = {x+1,y};
                if(matrix[y][x+1] != 0)          //right
                {
                    if(!hadVisited.count(&matrix[rightPoint.y][rightPoint.x+1]))
                    {
                        nxtLevelNum++;
                        data.push(rightPoint);
                        hadVisited.insert(&matrix[rightPoint.y][rightPoint.x+1]);
                    }
                }
                else
                {
                    return level;
                }
            }
            if(y >= 0 && y < matrix.size()-1)  //down
            {
                cout<<"down"<<endl;
                Point downPoint = {x,y+1};
                if(matrix[y+1][x] != 0)         
                {
                    if(!hadVisited.count(&matrix[downPoint.y+1][downPoint.x]))
                    {
                        nxtLevelNum++;
                        data.push(downPoint);
                        hadVisited.insert(&matrix[downPoint.y+1][downPoint.x]);
                    }
                }
                else
                {
                    return level;
                }
            }
            if(y > 0 && y <= matrix.size()-1)  //up
            {
                Point upPoint = {x,y-1};
                if(matrix[y-1][x] != 0)         
                {
                    if(!hadVisited.count(&matrix[upPoint.y-1][upPoint.x]))
                    {
                        nxtLevelNum++;
                        data.push(upPoint);
                        hadVisited.insert(&matrix[upPoint.y-1][upPoint.x]);
                    }
                }
                else
                {
                    return level;
                }
            }
            if(curLevelNum == 0)
            {
                curLevelNum = nxtLevelNum;
                nxtLevelNum = 0;
                level++;
            }
        }
        return INT_MAX;
    }
};
int main()
{
    vector<vector<int>> image = {{0,0,0,1},{0,1,0,0},{1,0,0,1},{1,1,1,1}};
    Solution so;
    so.updateMatrix(image);
    for(vector<vector<int>>::const_iterator i = image.cbegin();i < image.cend();i++)
    {
        for(vector<int>::const_iterator j = (*i).cbegin() ; j <(*i).cend();j++)
        {
            cout<<*j;
        }
        cout<<endl;
    }
}