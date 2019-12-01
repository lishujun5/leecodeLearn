#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class getMatrix{
    private:
        vector<vector<int>> data; 
        bool fileAvaliable;
    public:
        getMatrix(string filename):fileAvaliable(0)
        {
            ifstream infile(filename);
            if(!infile)
            {
                fileAvaliable = 0;
                cerr<<"file open error"<<endl;
            }
            else
            {
                fileAvaliable = 1;
                int tmp;
                string lineData;
                while(getline(infile,lineData))
                {
                    vector<int> linedata;
                    istringstream tmpLineDateString(lineData);
                    while(tmpLineDateString>>tmp)
                    {
                        linedata.push_back(tmp);
                    }
                    data.push_back(linedata);
                }
            }
        }
        bool isFileAvaliable()
        {
            return fileAvaliable;
        }
        void print_data(vector<vector<int>> data)
        {
            for(auto e:data)
            {
                for(auto q:e)
                {
                    cout<<q<<" ";
                }
                cout<<endl;
            }
        }
        vector<vector<int>> getData()
        {
            return data;
        }

};
class Solution
{
    public:
        void wallsAndGates(vector<vector<int>> data)
        {
            
        }
};

int main()
{
    auto p_matrix = new getMatrix("./wall_and_door.txt");
    if(!p_matrix->isFileAvaliable())
    {
        cout<<"create failed"<<endl;
        return -1;
    }
    p_matrix->print_data(p_matrix->getData());
    getchar();
}