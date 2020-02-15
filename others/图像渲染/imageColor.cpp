#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int preColor = image[sc][sr];
        image[sc][sr] = newColor;
        if(sc >= 0 && sc < image.size()-1)  //down
        {
            if(image[sc+1][sr] == preColor)
            {
                floodFill(image,sr,sc+1,newColor);
            }
        }
        if(sc > 0 && sc <= image.size()-1)     //up
        {
            if(image[sc-1][sr] == preColor)
            {
                floodFill(image,sr,sc-1,newColor);
            }
        }
        if(sr >= 0 && sr < image[0].size()-1)   //right
        {
            if(image[sc][sr+1] == preColor)
            {
                floodFill(image,sr+1,sc,newColor);
            }
        }
        if(sr > 0 && sr <= image[0].size()-1)       //left
        {
            if(image[sc][sr-1] == preColor)
            {
                floodFill(image,sr-1,sc,newColor);
            }
        }
        return image;
    }
};
int main()
{
    vector<vector<int>> image = {{{1,1,1},{1,1,0},{1,0,1}}};
    Solution so;
    so.floodFill(image,1,1,2);
    for(vector<vector<int>>::const_iterator i = image.cbegin();i < image.cend();i++)
    {
        for(vector<int>::const_iterator j = (*i).cbegin() ; j <(*i).cend();j++)
        {
            cout<<*j;
        }
        cout<<endl;
    }
}